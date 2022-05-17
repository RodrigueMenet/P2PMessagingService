#pragma once

#include "IPublisher.h"
#include "IReplier.h"

#include <map>
#include <future>
#include <list>

struct P2PService
{
  P2PService(IReplier& registry,  IPublisher& notifier);
  void Start();
  void Stop();
  void WaitForShutDown();

private:
  std::future<void> mAsyncDo;
  std::atomic<bool> Stopped = false;
  IReplier& mRegistry;
  IPublisher& mNotifier;
  std::list<uint8_t> ClientUIDs;
};
