#include "ZmqPublisher.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <zmq.h>


ZmqPublisher::ZmqPublisher(void* socket, const std::string& url)
  : mSocket(socket), mUrl(url)
{
}


void ZmqPublisher::Start()
{
  auto rc = zmq_bind(mSocket, mUrl.c_str());
  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_bind " << zmq_strerror(errno) << std::endl;
    throw std::exception(ss.str().c_str());
  }
}


void ZmqPublisher::Stop()
{
  const auto rc = zmq_close(mSocket);
  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_close " << zmq_strerror(errno) << std::endl;
    throw std::exception(ss.str().c_str());
  }
}


void ZmqPublisher::Send(const IMessage& message)
{
  const auto rc = zmq_send(mSocket, message.Data(), message.Size(), 0);
  if(rc != message.Size())
  {
    std::cerr << __FUNCTION__ << " " << "rc = " << rc << std::endl;
  }
}
