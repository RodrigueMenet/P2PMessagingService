#pragma once

#include <string>

#include "ISubscriber.h"
#include "IReplier.h"
#include "IRequester.h"
#include "IPublisher.h"

const auto SERVER_URL = "127.0.0.1";
const auto SERVER_PORT = 1337;


inline std::string BuildServerCompleteUrl(bool publisher)
{
  return std::string("tcp://") + SERVER_URL + ":" + std::to_string(SERVER_PORT + (publisher ? 1 : 0));
}


inline std::string BuildPeerCompleteUrl(int id)
{
  return std::string("tcp://") + SERVER_URL + ":" + std::to_string(SERVER_PORT + id + 1);
}


struct ZmqFactory
{
  ZmqFactory();
  std::shared_ptr<ISubscriber> BuildSubscriber(std::string const& url) const;
  std::shared_ptr<IPublisher> BuildPublisher(std::string const& url) const;
  std::shared_ptr<IRequester> BuildRequester(std::string const& url) const;
  std::shared_ptr<IReplier> BuildReplier(std::string const& url) const;
private:
  void* mContext;
};
