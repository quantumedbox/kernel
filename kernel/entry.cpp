#include "display/display.hpp"
#include "io/port.hpp"
#include "std/string.hpp"
#include "cpu/x86.hpp"

using namespace VgaDisplay;

#define DO_INFINITE_LOOP() do { while (1) { __asm__ ("hlt"); } } while (0)

static void keyboard_callback(CPU::Registers* r) {
  (void)r;
  static constexpr IO::Port scancode_register { 0x60 };
  volatile uint8_t scancode = scancode_register.take_byte();
  put_uint32(scancode);
}

// static void timer_callback(CPU::Registers* r) {
//   (void)r;
//   put_uint32(0);
//   newline_offset();
// }

extern "C" void kernel_entry() {
  CPU::idt_init();
  CPU::enable_interrupts();
  CPU::register_interrupt_handler(CPU::IRQ1, keyboard_callback);
  // CPU::register_interrupt_handler(CPU::IRQ0, timer_callback);

  set_style(init_style<Color::LightGray, Color::Blue>());
  fill_screen(' ');

  // IO::SerialPort COM1 { IO::SERIAL_PORT_ADDRESSES[0] };
  // if (COM1.is_ok()) {
  //   put_string(string_from_literal("COM1 is ok"));
  //   COM1.put_byte('t');
  // } else
  //   put_string(string_from_literal("couldn't initialize COM1"));

  set_style(init_style<Color::Yellow, Color::Black>());
  put_string(string_from_literal("hello world"));

  newline_offset();

  set_style(init_style<Color::Red, Color::LightGray>());
  put_string(string_from_literal("attempt to exit kernel entry, halt in infinite loop"));

  set_cursor_pos(get_offset()/2);

  DO_INFINITE_LOOP();
}
