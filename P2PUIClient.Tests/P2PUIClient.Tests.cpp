#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "fakeit.hpp"

#include "P2PClient.h"
#include "SimpleMessage.h"

TEST_CASE("P2PClient")
{
  fakeit::Mock<IRequester> mock_server_requester;
  fakeit::Mock<ISubscriber> mock_server_subscriber;
  fakeit::Mock<IReplier> mock_peer_replier;
  fakeit::Mock<IRequester> mock_peer_requester;
  fakeit::Fake(Dtor(mock_peer_requester)); // else dtor is called when shared_ptr is released, leading to a sefault


  const auto CLIENT_UID = 16;
  P2PClient client(mock_server_requester.get(), mock_server_subscriber.get(), mock_peer_replier.get(), CLIENT_UID);

  SECTION("Client registration -> UID sent")
  {
    fakeit::When(Method(mock_server_requester, Start)).Return();
    fakeit::When(Method(mock_server_subscriber, Start)).Return();
    uint8_t received_uid;
    fakeit::When(Method(mock_server_requester, Request)).Do([&received_uid](const IMessage& message)
    {
      received_uid = message.SpecificPayload<PeerRegisterPayload>()->UID;
      return nullptr;
    });
    client.ConnectToServer();
    CHECK(received_uid == CLIENT_UID);

    SECTION("Peers available received -> peers ids returned")
    {
      fakeit::When(Method(mock_server_subscriber, Receive)).Do([](int& i)
      {
        return std::make_unique<PayloadMessage<PeersAvailablePayload>>(MessageType::PeersAvailable, PeersAvailablePayload{1, 2, 4, 6});
      });
      const auto peer_ids = client.ReceiveMessageFromServer(10);
      CHECK(peer_ids.size() == 4);
      CHECK(peer_ids[0] == 1);
      CHECK(peer_ids[1] == 2);
      CHECK(peer_ids[2] == 4);
      CHECK(peer_ids[3] == 6);
    }

    SECTION("Send message to a peer")
    {
      client.AddPeer(1, std::shared_ptr<IRequester>(&mock_peer_requester.get()));
      std::wstring received_msg;
      fakeit::When(Method(mock_peer_requester, Request)).Do([&received_msg](const IMessage& message)

      {
        const auto msg = message.SpecificPayload<PeerDisplayMessage>()->Message;
        received_msg.assign(msg, wcslen(msg));
        return nullptr;
      });
      fakeit::When(Method(mock_peer_requester, Stop)).Return();
      const auto SENT_MSG = L"Hello";
      client.SendMessageToPeer(1, SENT_MSG);

      CHECK_FALSE(received_msg.find(SENT_MSG) == std::wstring::npos);
    }
  }

  fakeit::When(Method(mock_server_requester, Stop)).Return();
  fakeit::When(Method(mock_server_subscriber, Stop)).Return();
  client.Stop();
}
