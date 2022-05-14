#pragma once
#include <memory>
#include <string>

#include "IPublisher.h"
#include "ISubscriber.h"
#include "IRequester.h"
#include "IReplier.h"


struct IMiddleWare
{
  virtual ~IMiddleWare() = default;
  virtual std::shared_ptr<IPublisher> BuildPublisher(std::string const& url) const = 0;
  virtual std::shared_ptr<ISubscriber> BuildSubscriber(std::string const& url) const = 0;
  virtual std::shared_ptr<IRequester> BuildRequester(std::string const& url) const = 0;
  virtual std::shared_ptr<IReplier> BuildReplier(std::string const& url) const = 0;
};
