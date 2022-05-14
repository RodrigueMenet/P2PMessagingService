#pragma once

#include <stdint.h>
#include <exception>


enum class MessageType : uint8_t
{
  PeerRegister = 0,
  PeersAvailable = 1,
  P2pMessage = 2,
  Life = 3,
  PeerRegisterAck = 4,
};


struct PeerRegisterPayload
{
  uint8_t UID;
};


struct PeersAvailablePayload
{
  uint8_t UIDs[20];
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
  const T& Payload() const;
  virtual size_t Size() const = 0;
};


template <typename T>
const T& IMessage::Payload() const
{
  if(Data() == nullptr || Size() < sizeof(T) + sizeof(Header))
    throw std::exception{"unexpected cast"};

  const auto& payload = Data() + sizeof(Header);

  return reinterpret_cast<const T&>(*payload);
}
