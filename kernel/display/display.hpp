#pragma once

#include <stdint.h>
#include <stddef.h>

#include "std/string.hpp"

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

uint16_t get_width();
uint16_t get_height();
inline uint32_t get_display_area() { return get_width() * get_height(); }

void set_cursor_pos(uint16_t offset);
uint16_t get_cursor_pos();

void set_style(StyleAttribute);
StyleAttribute get_style();

/*
  Character Offset
  Specifies the position on which next drawing command will take place
  'Put' family of functions always moves the offset so you can use it for sequential printing
*/
void set_offset(uint16_t offset);
uint16_t get_offset();

/* WARNING: all printing function which depend on some global state (aka offset and style)
            shouldn't be used inside exception handlers as there's no guarantee that interrupt doesn't
            come from another printing call which haven't changed the state yet
*/

/*
  @brief  Moves offset to the next line compared to current offset
*/
void newline_offset();

void put_char(uint8_t);
void put_string(const KS::StringView);
void put_uint32(uint32_t);

void fill_screen(uint8_t ch);

void hide_cursor();

}
