#include "multiboot1/header.h"

#include "display/display.hpp"
#include "io/port.hpp"
#include "std/string.hpp"
#include "cpu/ldt.hpp"
#include "io/keyboard.hpp"
#include "display/style.hpp"
#include "panic.hpp"

// to read: https://wiki.osdev.org/Detecting_Memory_(x86)

using namespace VgaDisplay;

constexpr Style shell_style;

extern "C" void kernel_entry(multiboot_info_t* info, uint32_t magic_number) {
  if (magic_number != MULTIBOOT_BOOTLOADER_MAGIC) {
    KS::panic(KS::StringView("invalid magic number"));
  }

  // if (!(info->flags >> 6 & 0x1)) {
  //   put_string(KS::StringView("invalid memory map"));
  //   goto error_label;
  // }

  CPU::idt_init();
  Keyboard::init();
  CPU::enable_interrupts();

  VgaDisplay::set_offset(0);
  VgaDisplay::set_style(shell_style.plain());
  VgaDisplay::fill_screen(' ');
  VgaDisplay::put_string(KS::StringView{"hello world"});

  // Keyboard::set_led_state(Keyboard::init_led_state<true, true, true>());

  // // IO::SerialPort COM1 { IO::SERIAL_PORT_ADDRESSES[0] };
  // // if (COM1.is_ok()) {
  // //   put_string(KS::StringView("COM1 is ok"));
  // //   COM1.put_byte('t');
  // // } else
  // //   put_string(KS::StringView("couldn't initialize COM1"));
  // // newline_offset();

  while (true);

  panic(KS::StringView{"Attempt to exit kernel_entry"});
}
