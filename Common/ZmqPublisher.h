#pragma once

#include <string>

#include "IPublisher.h"


struct ZmqPublisher : IPublisher
{
  ZmqPublisher(void* socket, const std::string& url);
  void Start() override;
  void Stop() override;
  void Send(const IMessage&) override;

private:
  void* mSocket;
  std::string const mUrl;
};
