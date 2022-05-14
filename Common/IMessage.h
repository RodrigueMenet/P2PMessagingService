#pragma once

#include <vector>


enum class MessageType : uint8_t
{
  PeerRegister = 0,
  PeerAvailable = 1,
  P2pMessage = 2,
  Life = 3,
};


struct Header
{
  MessageType Idx;
};


struct IMessage
{
  virtual ~IMessage() = default;
  virtual Header GetHeader() const = 0;
  virtual const uint8_t* Data() const = 0;
  template <typename T>
  const T& PlainData() const;
  virtual size_t Size() const = 0;
};


template <typename T>
const T& IMessage::PlainData() const
{
  if(Data() == nullptr || Size() < sizeof(T))
    throw std::exception{"unexpected cast"};

  return reinterpret_cast<const T&>(*Data());
}
