#pragma once

#include <vector>

#include "IMessage.h"


struct ZmqReceivedMessage : IMessage
{
  ZmqReceivedMessage();
  MsgHeader Header() const override;
  const uint8_t* Data() const override;
  const uint8_t* Payload() const override;
  size_t Size() const override;

  uint8_t* Data();
  void SetSize(size_t);

private:
  std::vector<uint8_t> mData;
};
