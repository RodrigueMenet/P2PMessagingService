#pragma once

#include "IMessage.h"


struct SimpleMessage : IMessage
{
  SimpleMessage(MessageType type);
  Header GetHeader() const override;
  const uint8_t* Data() const override;
  size_t Size() const override;
private:
  MessageType mType;
};


inline SimpleMessage::SimpleMessage(MessageType type)
  : mType(type)
{
}


inline Header SimpleMessage::GetHeader() const
{
  return {mType};
}


inline const uint8_t* SimpleMessage::Data() const
{
  return reinterpret_cast<const uint8_t*>(&mType);
}


inline size_t SimpleMessage::Size() const
{
  return sizeof(mType);
}


template <typename T>
struct PayloadMessage : IMessage
{
  PayloadMessage(MessageType type, const T& payload);
  Header GetHeader() const override;
  const uint8_t* Data() const override;
  size_t Size() const override;
private:
  MessageType mType;
  T mPayload;
};


template <typename T>
PayloadMessage<T>::PayloadMessage(MessageType type, const T& payload)
  : mType(type)
    , mPayload(payload)
{
}


template <typename T>
Header PayloadMessage<T>::GetHeader() const
{
  return {mType};
}


template <typename T>
const uint8_t* PayloadMessage<T>::Data() const
{
  return reinterpret_cast<const uint8_t*>(&mType);
}


template <typename T>
size_t PayloadMessage<T>::Size() const
{
  return sizeof(mType) + sizeof(mPayload);
}
