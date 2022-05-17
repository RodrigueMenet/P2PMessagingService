#include "ZmqFactory.h"

#include <sstream>
#include <zmq.h>

#include "ZmqPublisher.h"
#include "ZmqReplier.h"
#include "ZmqRequester.h"
#include "ZmqSubscriber.h"


/*****************************************************************************
 * @brief constructor
 ****************************************************************************/
ZmqFactory::ZmqFactory()
  : mContext(zmq_ctx_new())
{
  auto rc = zmq_ctx_set(mContext, ZMQ_IO_THREADS, 2);

  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_ctx_set threads" << rc << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  rc = zmq_ctx_set(mContext, ZMQ_MAX_SOCKETS, 128);

  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_ctx_set sockets" << rc << std::endl;
    throw std::exception{ss.str().c_str()};
  }
}


/*****************************************************************************
 * @brief Create a publisher object
 ****************************************************************************/
std::shared_ptr<IPublisher> ZmqFactory::BuildPublisher(std::string const& url) const
{
  auto* const socket = zmq_socket(mContext, ZMQ_PUB);

  if(socket == nullptr)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_socket ZMQ_PUB errno " << errno << std::endl;
    throw std::exception(ss.str().c_str());
  }

  return std::make_shared<ZmqPublisher>(socket, url);
}


std::shared_ptr<IRequester> ZmqFactory::BuildRequester(std::string const& url) const
{
  auto* const socket = zmq_socket(mContext, ZMQ_REQ);

  if(socket == nullptr)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_socket ZMQ_PUB errno " << errno << std::endl;
    throw std::exception(ss.str().c_str());
  }

  return std::make_shared<ZmqRequester>(socket, url);
}


std::shared_ptr<IReplier> ZmqFactory::BuildReplier(std::string const& url) const
{
  auto* const socket = zmq_socket(mContext, ZMQ_REP);

  if(socket == nullptr)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_socket ZMQ_PUB errno " << errno << std::endl;
    throw std::exception(ss.str().c_str());
  }

  return std::make_shared<ZmqReplier>(socket, url);
}


/*****************************************************************************
 * @brief Create a subscriber object
 ****************************************************************************/
std::shared_ptr<ISubscriber> ZmqFactory::BuildSubscriber(std::string const& url) const
{
  auto* const socket = zmq_socket(mContext, ZMQ_SUB);

  if(socket == nullptr)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_socket ZMQ_SUB errno " << errno << std::endl;
    throw std::exception(ss.str().c_str());
  }

  return std::make_shared<ZmqSubscriber>(socket, url);
}
