#include "P2PService.h"

#include <iostream>

#include "SimpleMessage.h"


P2PService::P2PService(IReplier& registry, IPublisher& notifier)
  : mRegistry(registry)
    , mNotifier(notifier)
{
}


void P2PService::Start()
{
  mRegistry.Start();
  mNotifier.Start();

  mAsyncRegister = std::async([this]()
  {
    while(Stopped == false)
    {
      const auto msg = mRegistry.Receive(10);

      if(msg && msg->Header().Id == MessageType::PeerRegister)
      {
        if(mClientUIDs.size() >= MAX_CLIENT_NUMBER)
        {
          std::cerr << "NEW client registration refused : max client number reached (" << MAX_CLIENT_NUMBER << ")";
          continue;
        }

        // update users list
        try
        {
          const auto newid = msg->SpecificPayload<PeerRegisterPayload>()->UID;
          mClientUIDs.push_back(newid);
          std::cout << "Client " << newid << " registered !" << std::endl;
        }
        catch(const std::exception& ex)
        {
          std::cerr << "NEW client registration refused : unexpected message content (err : " << ex.what() << ")";
          continue;
        }

        mRegistry.Send(SimpleMessage(MessageType::PeerRegisterAck));

        
        // build new list
        PeersAvailablePayload payload{};
        auto i = 0;
        for(const auto& client : mClientUIDs)
        {
          payload.UIDs[i++] = client;
        }
        // warn also other users, about up to date user list
        mNotifier.Send(PayloadMessage<PeersAvailablePayload>{MessageType::PeersAvailable, payload});
      }
    }
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
  mAsyncRegister.get();
  mRegistry.Stop();
  mNotifier.Stop();
}
