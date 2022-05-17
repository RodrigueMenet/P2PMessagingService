#pragma once
#include "IMessage.h"
#include <memory>


struct IRequester
{
  virtual ~IRequester() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual std::unique_ptr<IMessage> Request(const IMessage&) = 0;
};
