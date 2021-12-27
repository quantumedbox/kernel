#include <limits.h>

#include "display.hpp"
#include "io/port.hpp"
#include "memory.h"

// helpful reference: http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A

#define IS_VISIBLE_ASCII(ch) ((ch) >= 0x20) && ((ch) <= 0x7e)
#define IS_PRINTABLE(ch) IS_VISIBLE_ASCII(ch) | ((ch) == '\n')
#define IS_STRING_AT_NULL(str) (*str == 0)

namespace VgaDisplay {

// those depend on currently selected mode
static uint16_t width = 80;
static uint16_t height = 25;

uint16_t get_width() { return width; }
uint16_t get_height() { return height; }

enum { CTRL_REGISTER = 0x03d4, DATA_REGISTER = 0x03d5 };
enum {
  CURSOR_START_REG = 0x0a, // 5th bit states whether cursor is enabled
  CURSOR_OFFSET_HIGH = 0x0e,
  CURSOR_OFFSET_LOW = 0x0f,
};

static constexpr IO::Port ctrl_port { CTRL_REGISTER };
static constexpr IO::Port data_port { DATA_REGISTER };

static volatile uint8_t* VIDEOMEM_BASE = (uint8_t*)0xb8000;
// position in VIDEOMEM_BASE that is expected to be used as output
static size_t current_offset = 0; // todo: make it size_t?
static StyleAttribute current_style = init_style<Color::White, Color::Black>();

struct StateCapture {
  uint16_t cursor;
  uint16_t offset;
  StyleAttribute style;

  inline StateCapture()
    : cursor (get_cursor_pos())
    , offset (get_offset())
    , style (get_style())
  {

  }

  inline void release() {
    set_cursor_pos(cursor);
    set_offset(offset);
    set_style(style);
  }

};

void set_cursor_pos(uint16_t offset) {
  ctrl_port.put_byte(CURSOR_OFFSET_LOW);
  data_port.put_byte(offset & 0xff);
  ctrl_port.put_byte(CURSOR_OFFSET_HIGH);
  data_port.put_byte(offset >> 8);
}

// todo: we can cache it in kernel memory
uint16_t get_cursor_pos() {
  ctrl_port.put_byte(CURSOR_OFFSET_HIGH);
  int16_t offset = data_port.take_byte() << 8;
  ctrl_port.put_byte(CURSOR_OFFSET_LOW);
  offset += data_port.take_byte();
  return offset;
}

void set_offset(uint16_t offset) {
  current_offset = (size_t)(offset * 2);
}

uint16_t get_offset() {
  return current_offset;
}

void set_style(StyleAttribute style) {
  current_style = style;
}

StyleAttribute get_style() {
  return current_style;
}

// todo: check whether offset is in bounds?
// todo: error propagation
void put_char(uint8_t character) {
  VIDEOMEM_BASE[current_offset] = character;
  VIDEOMEM_BASE[current_offset + 1] = (uint8_t)current_style;
  current_offset += 2;
}

// todo: kinda not ideal to use macro
#define put_string_impl_expand(xxx_string) do { \
  if (!IS_POINTER_VALID((xxx_string).chars)) \
    return; \
  for (size_t xxx_idx = 0; xxx_idx < (xxx_string).len; ++xxx_idx) { \
    uint8_t xxx_ch = (xxx_string).chars[xxx_idx]; \
    if (IS_PRINTABLE(xxx_ch)) \
      put_char(xxx_ch); \
  } \
} while (0)

void put_string(const String string) {
  put_string_impl_expand(string);
}

void put_uint32(uint32_t value) {
  const size_t MAX_CHARS = 3 * sizeof(uint32_t) * CHAR_BIT / 8;

  uint8_t builder_buff[MAX_CHARS];
  uint32_t builder_idx = MAX_CHARS;

  uint32_t reductor = value;
  do {
    builder_buff[--builder_idx] = (reductor % 10) + 0x30;
    reductor /= 10;
  } while (reductor != 0);

  put_string_impl_expand(init_string(&builder_buff[builder_idx], MAX_CHARS - builder_idx));
}

void newline_offset() {
  set_offset(((get_offset() / width) + 1) * width);
}

void fill_screen(uint8_t ch) { 
  for (uint32_t i = get_display_area(); i--;) {
    VIDEOMEM_BASE[i * 2] = ch;
    VIDEOMEM_BASE[i * 2 + 1] = (uint8_t)current_style;
  }
}

void hide_cursor() {
  ctrl_port.put_byte(CURSOR_START_REG);
  data_port.put_byte(0x01 << 5);
  ctrl_port.put_byte(CURSOR_START_REG);
  data_port.put_byte(0x01 << 5);
}

}
