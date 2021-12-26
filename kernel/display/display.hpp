#pragma once

#include <stdint.h>
#include <stddef.h>

#include "std/types.hpp"

// todo: additional 0x13 mode for image output
// todo: font overriding, possibly for creating cursors and other more complex things

namespace VgaDisplay {

using StyleAttribute = uint8_t;

enum class Color : uint8_t {
  Black,
  Blue,
  Green,
  Cyan,
  Red,
  Magenta,
  Brown,
  LightGray,
  DarkGray,
  LightBlue,
  LightGreen,
  LightCyan,
  LightRed,
  Pink,
  Yellow,
  White,
};

/*
  Statically construct VGA attribute

  @brief Exact meaning of many of bits is dependent on concrete VGA mode, this just assumes one of valid ways

  @return StyleAttribute value that is valid for set_style() call
*/
template <Color foreground, Color background, bool blink_bit = false>
constexpr StyleAttribute init_style()
{
  static_assert((uint8_t)foreground <= (1 << 4));
  static_assert((uint8_t)background <= (1 << 3));

  uint8_t result = (uint8_t)foreground;
  result |= (uint8_t)background << 4;
  result |= (uint8_t)blink_bit << 7; 

  return result;
}

// void init();

uint16_t get_width();
uint16_t get_height();
inline uint32_t get_display_area() { return get_width() * get_height(); }

void set_cursor_pos(uint16_t offset);
uint16_t get_cursor_pos();

void set_style(StyleAttribute);
StyleAttribute get_style();

// todo: better name
void set_offset(uint16_t offset);
uint16_t get_offset();

void put_char(uint8_t);
// void put_null_string(const uint8_t*);
void put_string(const String);
void put_uint32(uint32_t);

void fill_screen(uint8_t ch);

void hide_cursor();

}
