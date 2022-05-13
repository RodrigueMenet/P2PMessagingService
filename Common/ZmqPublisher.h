#pragma once

#include "IPublisher.h"


struct ZmqPublisher : IPublisher
{
  ZmqPublisher(void* socket, const std::string& url);
  void Start() override;
  void Stop() override;
  void Send(const Message&) override;

private:
  void* mSocket;
  std::string const mUrl;
};
