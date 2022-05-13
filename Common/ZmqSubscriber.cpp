#include "ZmqSubscriber.h"

#include <ostream>
#include <sstream>
#include <zmq.h>


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


Message ZmqSubscriber::Receive(size_t size)
{
  Message msg(size);
  const auto recv = zmq_recv(mSocket, msg.data(), msg.size(), 0);

  if(recv < 0)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " receive data " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  if(recv != msg.size())
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "wrong message received size " << recv << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  return msg;
}


void ZmqSubscriber::SetTimeout(int timeout_ms)
{
  const auto rc = zmq_setsockopt(mSocket, ZMQ_RCVTIMEO, &timeout_ms, sizeof(timeout_ms));

  if(rc < 0)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "error when defining timeout " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }
}
