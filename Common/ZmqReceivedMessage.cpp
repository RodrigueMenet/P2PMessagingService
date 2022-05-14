#include "ZmQReceivedMessage.h"

void ZmqReceivedMessage::SetSize(size_t newsize)
{
  mData.resize(newsize);
}


const auto MAX_MESSAGE = 256;


ZmqReceivedMessage::ZmqReceivedMessage()
{
  mData.resize(MAX_MESSAGE);
}


Header ZmqReceivedMessage::GetHeader() const
{
  return {static_cast<MessageType>(mData.at(0))};
}


const uint8_t* ZmqReceivedMessage::Data() const
{
  return mData.data();
}


size_t ZmqReceivedMessage::Size() const
{
  return mData.size();
}


uint8_t* ZmqReceivedMessage::Data()
{
  return mData.data();
}
