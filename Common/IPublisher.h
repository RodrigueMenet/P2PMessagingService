#pragma once
#include <string>

#include "Message.h"


struct IPublisher
{
  virtual ~IPublisher() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Send(const Message&) = 0;
};
