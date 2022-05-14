#pragma once
#include <memory>

#include "IMessage.h"


struct IReplier
{
  virtual ~IReplier() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual std::unique_ptr<IMessage> Receive() = 0;
  virtual void Send(const IMessage&) = 0;
  virtual void SetTimeout(int timeout_ms) = 0;
};
