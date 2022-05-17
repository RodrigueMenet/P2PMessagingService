#pragma once

#include <stdint.h>
#include <exception>


enum class MessageType : uint8_t
{
  Unknown = 0xff,
  PeerRegister = 0,
  PeersAvailable = 1,
  PeerMessage = 2
};


struct PeerRegisterPayload
{
  uint8_t UID;
};


constexpr auto MAX_CLIENT_NUMBER = 100;


struct PeersAvailablePayload
{
  uint8_t UIDs[MAX_CLIENT_NUMBER];
};


constexpr auto MAX_MESSAGE_SIZE = 200;


struct PeerDisplayMessage
{
  wchar_t Message[MAX_MESSAGE_SIZE];
};


struct MsgHeader
{
  MessageType Id;
};


struct IMessage
{
  virtual ~IMessage() = default;
  virtual MsgHeader Header() const = 0;
  virtual const uint8_t* Data() const = 0;
  virtual const uint8_t* Payload() const = 0;
  template <typename T>
  const T* SpecificPayload() const;
  virtual size_t Size() const = 0;
};


template <typename T>
const T* IMessage::SpecificPayload() const
{
  if(Payload() == nullptr || Size() < sizeof(T) + sizeof(MsgHeader))
    throw std::exception{"unexpected cast"};

  return reinterpret_cast<const T*>(Payload());
}
