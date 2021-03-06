#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "fakeit.hpp"
#include "P2PService.h"
#include "SimpleMessage.h"

TEST_CASE("P2PService")
{
  SECTION("Service start")
  {
    fakeit::Mock<IReplier> mock_registry;
    fakeit::Mock<IPublisher> mock_notifier;
    P2PService service(mock_registry.get(), mock_notifier.get());

    fakeit::When(Method(mock_registry, Start)).Return();
    fakeit::When(Method(mock_registry, Stop)).Return();
    fakeit::When(Method(mock_notifier, Start)).Return();
    fakeit::When(Method(mock_notifier, Stop)).Return();

    SECTION("No message -> always timeout")
    {
      fakeit::When(Method(mock_registry, Receive)).AlwaysDo([](int& timeoutMs)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));
        return nullptr;
      });

      CHECK_NOTHROW(service.Start());
    }

    SECTION("Not managed message have been received -> no sent data")
    {
      fakeit::When(Method(mock_registry, Receive)).AlwaysDo([](int& timeoutMs)
      {
        return std::make_unique<SimpleMessage>(MessageType::PeerMessage);
      });

      CHECK_NOTHROW(service.Start());
      // registry::send not mocked up -> ok
    }
    SECTION("Register message have been received")
    {
      SECTION("With Unexpected payload -> no registration")
      {
        bool sent_once = false;
        fakeit::When(Method(mock_registry, Receive)).AlwaysDo([&sent_once](int& timeoutMS)
        {
          return std::make_unique<SimpleMessage>(sent_once ? MessageType::PeersAvailable : MessageType::PeerRegister);
        });
        CHECK_NOTHROW(service.Start());
      }

      SECTION("With Expected payload -> ack + updated list sent")
      {
        bool sent_once = false;

        fakeit::When(Method(mock_registry, Receive)).AlwaysDo([&sent_once](int& timeoutMS)
        {
          std::unique_ptr<IMessage> sent_msg = sent_once
                                                 ? nullptr
                                                 : std::make_unique<PayloadMessage<PeerRegisterPayload>>(MessageType::PeerRegister, PeerRegisterPayload{1});
          sent_once = true;
          return sent_msg;
        });

        fakeit::When(Method(mock_registry, Send)).Return();


        MessageType sent_notifier_id = MessageType::Unknown;

        fakeit::When(Method(mock_notifier, Send)).Do([&sent_notifier_id](const IMessage& message)
        {
          sent_notifier_id = message.Header().Id;
        });

        CHECK_NOTHROW(service.Start());

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        CHECK(sent_notifier_id == MessageType::PeersAvailable);
      }
    }


    SECTION("3 Register message have been received -> 3 UIDs are sent back to any listener")
    {
      uint8_t UID = 1;

      fakeit::When(Method(mock_registry, Receive)).AlwaysDo([&UID](int& timeoutMS)
      {
        std::unique_ptr<IMessage> sent_msg = UID > 3
                                               ? nullptr
                                               : std::make_unique<PayloadMessage<PeerRegisterPayload>>(MessageType::PeerRegister, PeerRegisterPayload{UID++});
        return sent_msg;
      });
      fakeit::When(Method(mock_registry, Send)).AlwaysReturn();

      std::vector<PeersAvailablePayload> sent_peer_payloads;
      fakeit::When(Method(mock_notifier, Send)).AlwaysDo([&sent_peer_payloads](const IMessage& message)
      {
        sent_peer_payloads.push_back(*message.SpecificPayload<PeersAvailablePayload>());
      });

      CHECK_NOTHROW(service.Start());

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      CHECK(sent_peer_payloads.size() == 3);

      CHECK(sent_peer_payloads.at(0).UIDs[0] == 1);
      CHECK(sent_peer_payloads.at(0).UIDs[1] == 0);

      CHECK(sent_peer_payloads.at(1).UIDs[0] == 1);
      CHECK(sent_peer_payloads.at(1).UIDs[1] == 2);
      CHECK(sent_peer_payloads.at(1).UIDs[2] == 0);

      CHECK(sent_peer_payloads.at(2).UIDs[0] == 1);
      CHECK(sent_peer_payloads.at(2).UIDs[1] == 2);
      CHECK(sent_peer_payloads.at(2).UIDs[2] == 3);
      CHECK(sent_peer_payloads.at(2).UIDs[3] == 0);
    }

    service.Stop();
  }
}
