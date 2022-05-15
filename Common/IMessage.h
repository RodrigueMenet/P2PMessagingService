#pragma once

#include <stdint.h>
#include <exception>


enum class MessageType : uint8_t
{
  Unknown = 0xff,
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


const auto MAX_CLIENT_NUMBER = 100;


struct PeersAvailablePayload
{
  uint8_t UIDs[MAX_CLIENT_NUMBER];
};


struct Header
{
  MessageType Id;
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
