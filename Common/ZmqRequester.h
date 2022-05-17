#pragma once

#include <memory>
#include <string>
#include "IRequester.h"


struct ZmqRequester : IRequester
{
  ZmqRequester(void* socket, std::string url);
  void Start() override;
  void Stop() override;
  std::unique_ptr<IMessage> Request(const IMessage&) override;

private:
  void* mSocket;
  std::string const mUrl;
};
