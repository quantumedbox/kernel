#include <stddef.h>

#include "keyboard.hpp"
#include "io/port.hpp"
#include "cpu/x86.hpp"

#include "display/display.hpp"

#define SCANCODE_BUFFER_CAPACITY 128

// todo: function for specifying specific layout set

namespace Keyboard {

enum class Mode : uint8_t {
  Unspecified,
  PS2,
};

static Mode current_mode = Mode::Unspecified;

/*
  All keyboard events should be stored here and then dispatch by specific implementation of dispatcher
*/
static uint8_t scancode_buffer[SCANCODE_BUFFER_CAPACITY];
static size_t scancode_buffer_cursor = 0; // position in scancode_buffer to which next writing will occur

static constexpr IO::Port ps2_register { 0x60 };

static void ps2_keyboard_callback(CPU::Registers* r) {
  (void)r;
  volatile uint8_t scancode = ps2_register.take_byte();
  if (scancode_buffer_cursor != SCANCODE_BUFFER_CAPACITY) {
    VgaDisplay::put_uint32(scancode);
    VgaDisplay::newline_offset();
    scancode_buffer_cursor++;
  }
  // todo: report error on buffer overflow
}

/*
  Initializes interrupt handler at IRQ1 for receiving inputs into the scancode_buffer
*/
void init_ps2() {
  CPU::register_interrupt_handler(CPU::IRQ1, ps2_keyboard_callback);
  current_mode = Mode::PS2;
}

void set_led_state(LedState state) {
  static const uint8_t ACKNOWLEDGEMENT = 0xfa;

  if (current_mode != Mode::PS2) {
    // todo: unimplemented error
  }

  ps2_register.put_byte(0xed);
  uint8_t response = ps2_register.take_byte();
  if (response != ACKNOWLEDGEMENT) {
    VgaDisplay::put_string(KS::String("cannot set LED state"));
  }
  ps2_register.put_byte((uint8_t)state);
}

}
