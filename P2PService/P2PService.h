#pragma once

#include "IPublisher.h"
#include "IReplier.h"

#include <map>
#include <future>
#include <list>
#include <mutex>

struct P2PService
{
  P2PService(IReplier& registry,  IPublisher& notifier);
  void Start();
  void Stop();
  void WaitForShutDown();

private:
  std::future<void> mAsyncRegister;
  std::atomic<bool> Stopped = false;
  IReplier& mRegistry;
  IPublisher& mNotifier;
  std::list<PeerUID> mClientUIDs;
};
