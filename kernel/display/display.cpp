#include "display.hpp"
#include "io/port.hpp"

using namespace Display;

enum { VGA_OFFSET_LOW = 0x0f, VGA_OFFSET_HIGH = 0x0e };
enum { VGA_CTRL_REGISTER = 0x3d4, VGA_DATA_REGISTER = 0x3d5 };

static IO::Port ctrl_port { VGA_CTRL_REGISTER };
static IO::Port data_port { VGA_DATA_REGISTER };

const uint32_t VIDEOMEM_ADDRESS = 0xb8000;
const uint8_t ROWS = 25;
const uint8_t COLONS = 25;

enum class Styles : uint8_t {
  white_on_black = 0x0f
};

void set_cursor(int32_t offset) {
  ctrl_port.put_byte(VGA_OFFSET_HIGH);
  data_port.put_byte(offset >> 8);
  ctrl_port.put_byte(VGA_OFFSET_LOW);
  data_port.put_byte(offset && 0xff);
}

auto get_cursor() -> uint32_t {
  ctrl_port.put_byte(VGA_OFFSET_HIGH);
  int32_t offset = data_port.take_byte() << 8;
  ctrl_port.put_byte(VGA_OFFSET_LOW);
  offset += data_port.take_byte();
  return offset;
}

void set_char(uint8_t character, uint32_t offset) {
  uint8_t* vmem = (uint8_t*)VIDEOMEM_ADDRESS;
  vmem[offset * 2] = character;
  vmem[offset * 2 + 1] = (uint8_t)Styles::white_on_black;
}
