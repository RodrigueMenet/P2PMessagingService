#pragma once
#include "IMiddleWare.h"
#include <map>
#include <future>
#include <list>

struct P2PService
{
  P2PService(IReplier& registry,  IPublisher& notifier);
  void Start(const std::string& serverurl);
  void Stop();
  void WaitForShutDown();

private:
  std::future<void> mAsyncDo;
  std::atomic<bool> Stopped = false;
  IReplier& mRegistry;
  IPublisher& mNotifier;
  std::list<uint8_t> ClientUIDs;
};
