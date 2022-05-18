#include "ZmqReplier.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <zmq.h>

#include "ZmqReceivedMessage.h"


ZmqReplier::ZmqReplier(void* socket, const std::string& url)
  : mSocket(socket), mUrl(url)
{
}


void ZmqReplier::Start()
{
  auto rc = zmq_bind(mSocket, mUrl.c_str());
  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_bind " << zmq_strerror(errno) << std::endl;
    throw std::exception(ss.str().c_str());
  }
}


void ZmqReplier::Stop()
{
  const auto rc = zmq_close(mSocket);
  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_close " << zmq_strerror(errno) << std::endl;
    throw std::exception(ss.str().c_str());
  }
}


std::unique_ptr<IMessage> ZmqReplier::Receive(int timeoutMs)
{
  SetTimeout(timeoutMs);
  auto msg = std::make_unique<ZmqReceivedMessage >();
  const auto recv = zmq_recv(mSocket, msg->Get(), msg->Size(), 0);

  if(recv < 0 && errno == EAGAIN)
  {
    return nullptr;
  }

  if(recv < 0) // error handling
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " receive data " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  msg->SetSize(recv);
  
  return msg;
}


void ZmqReplier::SetTimeout(int timeout_ms)
{
  if(mTimeoutMs == timeout_ms)
    return;

  const auto rc = zmq_setsockopt(mSocket, ZMQ_RCVTIMEO, &timeout_ms, sizeof(timeout_ms));

  if(rc < 0)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "error when defining timeout " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  mTimeoutMs = timeout_ms;
}


void ZmqReplier::Send(const IMessage& message)
{
  const auto rc = zmq_send(mSocket, message.Data(), message.Size(), 0);
  if(rc != message.Size())
  {
    std::cerr << __FUNCTION__ << " " << "rc = " << rc << std::endl;
  }
}
