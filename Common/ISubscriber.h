#pragma once
#include <memory>

#include "IMessage.h"


struct ISubscriber
{
  virtual ~ISubscriber() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual std::unique_ptr<IMessage> Receive(int timeoutMs) = 0;
};
