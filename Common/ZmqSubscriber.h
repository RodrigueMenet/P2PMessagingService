#pragma once

#include "ISubscriber.h"


struct ZmqSubscriber : ISubscriber
{
  ZmqSubscriber(void* socket, std::string url);
  void Start() override;
  void Stop() override;
  Message Receive(size_t) override;
  void SetTimeout(int timeout_ms) override;
private:
  void* mSocket;
  std::string const mUrl;
};
