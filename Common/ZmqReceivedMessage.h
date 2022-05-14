#pragma once

#include <vector>

#include "IMessage.h"


struct ZmqReceivedMessage : IMessage
{
  ZmqReceivedMessage();
  Header GetHeader() const override;
  const uint8_t* Data() const override;
  size_t Size() const override;

  uint8_t* Data();
  void SetSize(size_t);

private:
  std::vector<uint8_t> mData;
};
