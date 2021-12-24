#include "port.hpp"

using namespace IO;

auto Port::take_byte() -> uint8_t {
  uint8_t result;
  asm("in %%dx, %%al" : "=a" (result) : "d" (m_port));
  return result;
}

void Port::put_byte(uint8_t data) {
  asm("out %%al, %%dx" : : "a" (data), "d" (m_port));
}
