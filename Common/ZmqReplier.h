#pragma once

#include <string>

#include "IReplier.h"


struct ZmqReplier : IReplier
{
  ZmqReplier(void* socket, const std::string& url);
  void Start() override;
  void Stop() override;
  std::unique_ptr<IMessage> Receive() override;
  void Send(const IMessage&) override;
  void SetTimeout(int timeout_ms) override;

private:
  void* mSocket;
  std::string const mUrl;
};
