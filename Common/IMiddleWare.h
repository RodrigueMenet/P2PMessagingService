#pragma once
#include <memory>
#include "IPublisher.h"
#include "ISubscriber.h"


struct IMiddleWare
{
  virtual ~IMiddleWare() = default;
  virtual std::shared_ptr<IPublisher> BuildPublisher(std::string const& url) const = 0;
  virtual std::shared_ptr<ISubscriber> BuildSubscriber(std::string const& url) const = 0;
};