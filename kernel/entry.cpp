#include "multiboot1/header.h"

#include "display/display.hpp"
#include "io/port.hpp"
#include "std/string.hpp"
#include "cpu/x86.hpp"
#include "io/keyboard.hpp"

using namespace VgaDisplay;

#define DO_INFINITE_LOOP() do { while (1) { __asm__ ("hlt"); } } while (0)

extern "C" void kernel_entry(multiboot_info_t* info, uint32_t magic_number) {
  if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC) {
    put_string(string_from_literal("invalid magic number"));
    goto error_label;
  }

  // if (!(info->flags >> 6 & 0x1)) {
  //   put_string(string_from_literal("invalid memory map"));
  //   goto error_label;
  // }

  CPU::idt_init();
  CPU::enable_interrupts();

  set_style(init_style<Color::LightGray, Color::Blue>());
  fill_screen(' ');

  Keyboard::init_ps2();
  Keyboard::set_led_state(Keyboard::init_led_state<true, true, true>());

  // // IO::SerialPort COM1 { IO::SERIAL_PORT_ADDRESSES[0] };
  // // if (COM1.is_ok()) {
  // //   put_string(string_from_literal("COM1 is ok"));
  // //   COM1.put_byte('t');
  // // } else
  // //   put_string(string_from_literal("couldn't initialize COM1"));
  // // newline_offset();

  set_style(init_style<Color::Yellow, Color::Black>());
  put_string(string_from_literal("hello world"));

  newline_offset();

  set_style(init_style<Color::Red, Color::LightGray>());
  put_string(string_from_literal("attempt to exit kernel entry, halt in infinite loop"));

  set_cursor_pos(get_offset());

error_label:
  DO_INFINITE_LOOP();
}
