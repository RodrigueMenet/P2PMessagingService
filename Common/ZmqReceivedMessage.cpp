#include "ZmQReceivedMessage.h"


const auto MAX_MESSAGE = 256;


ZmqReceivedMessage::ZmqReceivedMessage()
{
}


MsgHeader ZmqReceivedMessage::Header() const
{
  const auto data = Data();
  MsgHeader header;
  header.Id = static_cast<MessageType>(*data);
  return header;
}


const uint8_t* ZmqReceivedMessage::Data() const
{
  return mPayload.data();
}


const uint8_t* ZmqReceivedMessage::Payload() const
{
  return Data() + sizeof(MsgHeader);
}


size_t ZmqReceivedMessage::Size() const
{
  return mSize;
}

uint8_t* ZmqReceivedMessage::Get()
{
  return mPayload.data();
}


void ZmqReceivedMessage::SetSize(size_t size)
{
  mSize = size;
}

