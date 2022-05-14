#include "P2PService.h"

#include <iostream>

#include "SimpleMessage.h"


P2PService::P2PService(IReplier& registry, IPublisher& notifier)
  : mRegistry(registry)
    , mNotifier(notifier)
{
}


void P2PService::Start(const std::string& serverurl)
{
  mRegistry.Start();
  mNotifier.Start();

  mAsyncDo = std::async([this]()
  {
    while(Stopped == false)
    {
      const auto msg = mRegistry.Receive(10);
      if(msg && msg->GetHeader().Idx == MessageType::PeerRegister)
      {
        // ack
        mRegistry.Send(SimpleMessage(MessageType::PeerRegisterAck));

        // update users list
        ClientUIDs.push_back(msg->Payload<PeerRegisterPayload>().UID);

        // build new list
        PeersAvailablePayload payload{};
        auto i = 0;
        for(const auto& client : ClientUIDs)
        {
          payload.UIDs[i++] = client;
        }

        // warn all users, about up to date user list
        mNotifier.Send(PayloadMessage<PeersAvailablePayload>{MessageType::PeersAvailable, payload});
      }
    }

    mRegistry.Stop();
    mNotifier.Stop();
  });
}


void P2PService::WaitForShutDown()
{
  std::cout << "Enter a key to stop" << std::endl;
  getchar();
}


void P2PService::Stop()
{
  Stopped = true;
}
