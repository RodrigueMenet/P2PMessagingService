#pragma once
#include "IMiddleWare.h"

const auto SERVER_URL = "127.0.0.1:1337";


struct ZmqFactory : IMiddleWare
{
  ZmqFactory();
  std::shared_ptr<ISubscriber> BuildSubscriber(std::string const& url) const;
  std::shared_ptr<IPublisher> BuildPublisher(std::string const& url) const;
private:
  void* mContext;
};
