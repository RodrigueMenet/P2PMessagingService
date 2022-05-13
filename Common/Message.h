#pragma once

#include <vector>

struct Header
{
  uint64_t Idx;
  uint64_t PayloadSize;
};


// response
struct Message : std::vector<uint8_t>
{
  Message()
  {
    resize(sizeof(struct Header));
    Header() = {};
  }


  Message(size_t size) : Message()
  {
    resize(sizeof(struct Header) + size);
    Header().PayloadSize = size;
  }


  const uint8_t* Payload() const
  {
    return data() + sizeof(struct Header);
  }


  const Header& Header() const
  {
    return *reinterpret_cast<const struct Header*>(data());
  }


  struct Header& Header()
  {
    return *reinterpret_cast<struct Header*>(data());
  }


  size_t payload_size() const
  {
    return Header().PayloadSize;
  }


  size_t size() const
  {
    return sizeof(struct Header) + Header().PayloadSize;
  }
};
