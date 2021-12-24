#pragma once

#include <inttypes.h>

namespace IO {

class Port {
private:
  const uint16_t m_port;

public:

  Port(uint16_t port)
    : m_port (port)
  {

  }

  uint8_t take_byte();
  void put_byte(uint8_t data);
};

}
