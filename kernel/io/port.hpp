#pragma once

#include <stdint.h>

// todo: check whether serial ports were initialized already
// todo: no need to store whether serial port is initialized for whole duration of SerialPort existence, it should be returned locally
// todo: make that copying or moving the SerialPort object doesn't invoke constructor with initialization
// todo: afaik all ports are below 0x1000 so we can assert for that

namespace IO {

class Port {
private:
  const uint16_t m_port;

public:

  constexpr Port(uint16_t port)
    : m_port (port)
  {

  }

  void put_byte(uint8_t data) const;
  uint8_t take_byte() const;
};

const uint16_t SERIAL_PORT_ADDRESSES[] = {
  0x03f8, // COM1
  0x02f8, // COM2
  0x03e8, // COM3
  0x02e8, // COM4
};

class SerialPort {
private:
  const uint16_t m_port;
  bool m_is_ok;

  bool initialize();

public:
  SerialPort(uint16_t addr)
    : m_port(addr)
    , m_is_ok(this->SerialPort::initialize())
  {

  };

  bool is_ok() const;
  void put_byte(uint8_t data) const;
  uint8_t take_byte() const;

};

}
