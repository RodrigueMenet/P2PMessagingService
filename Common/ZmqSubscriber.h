#pragma once

#include <string>
#include "ISubscriber.h"


struct ZmqSubscriber : ISubscriber
{
  ZmqSubscriber(void* socket, std::string url);
  void Start() override;
  void Stop() override;
  std::unique_ptr<IMessage> Receive(int timeoutMs) override;
private:
  void SetTimeout(int timeout_ms);
  int mTimeoutMs = 0;
  void* mSocket;
  std::string const mUrl;
};
