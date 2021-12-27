#include "port.hpp"

namespace IO {

static inline void put_byte(uint16_t port, uint8_t data) {
  asm volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

static inline uint8_t take_byte(uint16_t port) {
  uint8_t result;
  asm volatile("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

static inline void put_word(uint16_t port, uint8_t data) {
  asm volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}

static inline uint8_t take_word(uint16_t port) {
  uint8_t result;
  asm volatile("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

uint8_t Port::take_byte() const {
  return IO::take_byte(m_port);
}

void Port::put_byte(uint8_t data) const {
  // VgaDisplay::put_uint32((uint32_t)m_port);
  IO::put_byte(m_port, data);
}

bool SerialPort::initialize() {
  static const uint8_t TEST_NUMBER = 0xaa;

  IO::put_byte(m_port + 1, 0x00);
  IO::put_byte(m_port + 3, 0x80);
  IO::put_byte(m_port + 0, 0x03);
  IO::put_byte(m_port + 1, 0x00);
  IO::put_byte(m_port + 3, 0x03);
  IO::put_byte(m_port + 2, 0xc7);
  IO::put_byte(m_port + 4, 0x0b);
  IO::put_byte(m_port + 4, 0x1e);
  IO::put_byte(m_port + 0, TEST_NUMBER);

  if (IO::take_byte(m_port) == TEST_NUMBER) {
    IO::put_byte(m_port + 4, 0x0f);
    return true;
  }
  return false;
}

bool SerialPort::is_ok() const {
  return m_is_ok;
}

void SerialPort::put_byte(uint8_t data) const {
  while (!(IO::take_byte(m_port + 5) & 0x20));
  IO::put_byte(m_port, data);
}

uint8_t SerialPort::take_byte() const {
  while (!(IO::take_byte(m_port + 5) & 1));
  return IO::take_byte(m_port);
}

}
