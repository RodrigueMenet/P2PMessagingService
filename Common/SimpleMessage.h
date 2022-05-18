#pragma once

#include "IMessage.h"


struct SimpleMessage : IMessage
{
  SimpleMessage(MessageType type);
  MsgHeader Header() const override;
  const uint8_t* Data() const override;
  const uint8_t* Payload() const override;
  size_t Size() const override;
private:
  MessageType mType;
};


inline SimpleMessage::SimpleMessage(MessageType type)
  : mType(type)
{
}


inline MsgHeader SimpleMessage::Header() const
{
  return {mType};
}


inline const uint8_t* SimpleMessage::Data() const
{
  return reinterpret_cast<const uint8_t*>(this);
}


inline const uint8_t* SimpleMessage::Payload() const
{
  return nullptr;
}


inline size_t SimpleMessage::Size() const
{
  return sizeof(*this);
}


template <typename T>
struct PayloadMessage : IMessage
{
  PayloadMessage(MessageType type, const T& payload);
  MsgHeader Header() const override;
  const uint8_t* Data() const override;
  const uint8_t* Payload() const override;
  size_t Size() const override;
private:
  struct ToSendData
  {
    MsgHeader mHeader;
    T mPayload;
  };


  ToSendData mToSend;
};


template <typename T>
PayloadMessage<T>::PayloadMessage(MessageType type, const T& payload)
  : mToSend{{type}, payload}
{
}


template <typename T>
MsgHeader PayloadMessage<T>::Header() const
{
  return mToSend.mHeader;
}


template <typename T>
const uint8_t* PayloadMessage<T>::Data() const
{
  return reinterpret_cast<const uint8_t*>(&mToSend);
}


template <typename T>
const uint8_t* PayloadMessage<T>::Payload() const
{
  return reinterpret_cast<const uint8_t*>(&mToSend.mPayload);
}


template <typename T>
size_t PayloadMessage<T>::Size() const
{
  return sizeof(mToSend);
}
