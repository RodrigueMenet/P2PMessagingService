#include "ZmqSubscriber.h"

#include <ostream>
#include <sstream>
#include <zmq.h>

#include "ZmqReceivedMessage.h"


ZmqSubscriber::ZmqSubscriber(void* socket, std::string url)
  : mSocket(socket), mUrl(std::move(url))
{
}


void ZmqSubscriber::Start()
{
  auto rc = zmq_connect(mSocket, mUrl.c_str());
  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_connect " << rc << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  rc = zmq_setsockopt(mSocket, ZMQ_SUBSCRIBE, nullptr, 0);

  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_setsockopt subscribe" << rc << std::endl;
    throw std::exception{ss.str().c_str()};
  }
}


void ZmqSubscriber::Stop()
{
  zmq_close(mSocket);
}


std::unique_ptr<IMessage> ZmqSubscriber::Receive(int timeoutMs)
{
  SetTimeout(timeoutMs);
  auto msg = std::make_unique<ZmqReceivedMessage>();
  const auto recv = zmq_recv(mSocket, msg->Get(), msg->Size(), 0);

  if(recv < 0)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " receive data " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }
  
  return msg;
}


void ZmqSubscriber::SetTimeout(int timeout_ms)
{
  if(mTimeoutMs == timeout_ms)
  {
    return;
  }

  const auto rc = zmq_setsockopt(mSocket, ZMQ_RCVTIMEO, &timeout_ms, sizeof(timeout_ms));

  if(rc < 0)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "error when defining timeout " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  mTimeoutMs = timeout_ms;
}
