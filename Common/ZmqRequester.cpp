#include "ZmqRequester.h"

#include <ostream>
#include <sstream>
#include <zmq.h>

#include "ZmqReceivedMessage.h"


ZmqRequester::ZmqRequester(void* socket, std::string url)
  : mSocket(socket), mUrl(std::move(url))
{
}


void ZmqRequester::Start()
{
  auto rc = zmq_connect(mSocket, mUrl.c_str());
  if(rc)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " " << "zmq_connect " << rc << std::endl;
    throw std::exception{ss.str().c_str()};
  }
}


void ZmqRequester::Stop()
{
  zmq_close(mSocket);
}


std::unique_ptr<IMessage> ZmqRequester::Request(const IMessage& msg)
{
  const auto rc = zmq_send(mSocket, msg.Data(), msg.Size(), 0);
  if(rc != msg.Size())
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " sent data " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }

  auto rcvd_msg = std::make_unique<ZmqReceivedMessage>();
  const auto recv = zmq_recv(mSocket, rcvd_msg->Get(), rcvd_msg->Size(), 0);

  if(recv < 0)
  {
    std::stringstream ss;
    ss << __FUNCTION__ << " receive data " << zmq_strerror(errno) << std::endl;
    throw std::exception{ss.str().c_str()};
  }
  
  return rcvd_msg;
}
