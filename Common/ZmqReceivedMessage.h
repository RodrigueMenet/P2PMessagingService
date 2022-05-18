#pragma once

#include <array>
#include <zmq.h>

#include "IMessage.h"


struct ZmqReceivedMessage : IMessage
{
  ZmqReceivedMessage();
  MsgHeader Header() const override;
  const uint8_t* Data() const override;
  const uint8_t* Payload() const override;
  size_t Size() const override;

  uint8_t* Get();
  void SetSize(size_t);

private:
  std::array<uint8_t, 64> mPayload;
  size_t mSize = 64;
};
