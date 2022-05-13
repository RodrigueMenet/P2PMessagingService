#pragma once
#include <string>

#include "Message.h"


struct ISubscriber
{
  virtual ~ISubscriber() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual Message Receive(size_t) = 0;
  virtual void SetTimeout(int timeout_ms) = 0;
};
