#include "display/display.hpp"
#include "io/port.hpp"
#include "std/types.hpp"

using namespace VgaDisplay;

#define DO_INFINITE_LOOP() do { while (1) { __asm__ ("hlt"); } } while (0)

extern "C" void kernel_entry() {
  set_style(init_style<Color::LightGray, Color::Blue>());
  fill_screen(' ');

  // IO::SerialPort COM1 { IO::SerialPortAddress::First };
  // if (COM1.is_ok()) {
  //   put_string(string_from_literal("COM1 is ok"));
  //   COM1.put_byte('t');
  // } else
  //   put_string(string_from_literal("couldn't initialize COM1"));

  set_style(init_style<Color::Yellow, Color::Black>());
  put_string(string_from_literal("hello world"));

  set_offset(get_width());

  set_style(init_style<Color::Red, Color::LightGray>());
  put_string(string_from_literal("attempt to exit kernel entry, halt in infinite loop"));

  set_cursor_pos(get_offset()/2);

  DO_INFINITE_LOOP();
}
