#pragma once
#include "IMessage.h"


struct IPublisher
{
  virtual ~IPublisher() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Send(const IMessage&) = 0;
};
