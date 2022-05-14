#pragma once

#include <string>

#include "IReplier.h"


struct ZmqReplier : IReplier
{
  ZmqReplier(void* socket, const std::string& url);
  void Start() override;
  void Stop() override;
  std::unique_ptr<IMessage> Receive(int timeoutMs) override;
  void Send(const IMessage&) override;

private:
  void SetTimeout(int timeout_ms);
  int mTimeoutMs;
  void* mSocket;
  std::string const mUrl;
};
