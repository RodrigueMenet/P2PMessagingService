#pragma once
#include "IMiddleWare.h"

struct ZmqFactory : IMiddleWare
{
  ZmqFactory();
  std::shared_ptr<ISubscriber> BuildSubscriber(std::string const& url) const;
  std::shared_ptr<IPublisher> BuildPublisher(std::string const& url) const;
private:
  void* mContext;
};
