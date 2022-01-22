#include <stddef.h>

#include "ps2_sets/set2.cpp"

#include "keyboard.hpp"
#include "io/port.hpp"
#include "cpu/ldt.hpp"
#include "display/display.hpp"
#include "std/array.hpp"
#include "panic.hpp"

static const size_t SCANCODE_BUFFER_CAPACITY = 128;

// todo: function for specifying specific layout set

namespace Keyboard {

enum class Mode : uint8_t {
  Uninitialized,
  PS2,
  USB, // todo: some day, maybe
};

static Mode current_mode = Mode::Uninitialized;

static KS::Array<uint8_t, SCANCODE_BUFFER_CAPACITY> scancode_buffer;
static size_t scancode_buffer_cursor = 0;

static constexpr IO::Port ps2_register { 0x60 };

namespace Response {
  const uint8_t Acknoledged = 0xfa;
  const uint8_t Resend = 0xfe;
  const uint8_t Echo = 0xee;
}

// todo: similar, but with limited N of attempts
#define AWAIT_BIND_RESPONSE(name) \
  uint8_t name; do { name = ps2_register.take_byte(); } while (name == Response::Resend)

#define AWAIT_RESPONSE() \
  do { uint8_t xxx_name; do { xxx_name = ps2_register.take_byte(); } while (xxx_name == Response::Resend); } while (0)

static void ps2_keyboard_callback(CPU::CpuState* r) {
  (void)r;
  volatile uint8_t scancode = ps2_register.take_byte();
  if (scancode_buffer_cursor != SCANCODE_BUFFER_CAPACITY) {
    VgaDisplay::put_uint32(scancode);
    VgaDisplay::newline_offset();
    scancode_buffer[scancode_buffer_cursor] = scancode;
    scancode_buffer_cursor++;
  } else
    assert(false, KS::StringView{"Keyboard scancode buffer overflow"});
}

static bool test_ps2() {
  ps2_register.put_byte(0xee);
  AWAIT_BIND_RESPONSE(response);
  return response == Response::Echo;
}

// for some reason on QEMU it returns 67 65 63 and responses, not sure whether it's how it's supposed to be or not
static uint8_t get_current_ps2_set() {
  ps2_register.put_byte(0xf0);
  AWAIT_RESPONSE();
  ps2_register.put_byte(0x0);
  AWAIT_RESPONSE();
  return ps2_register.take_byte();  
}

static bool try_setting_ps2_set(uint8_t set) {
  ps2_register.put_byte(0xf0);
  AWAIT_RESPONSE();
  ps2_register.put_byte(set);
  AWAIT_RESPONSE();
  return set == get_current_ps2_set(); // it should return the same set that was queued
}

/*
  Tries to find a keyboard and set its scancode page set if it's PS2 keyboard
  Initializes interrupt handler at IRQ1 for receiving inputs into the scancode_buffer

  todo: for now set 2 is assumed when ps2 is echoed properly, but it might not be so universal, not that we care much tho
*/
void init() {
  if (test_ps2()) {
    current_mode = Mode::PS2;
    CPU::register_interrupt_handler(CPU::IRQ1, ps2_keyboard_callback);
    try_setting_ps2_set(1);
  } else
    panic(KS::StringView{"Cannot identify the keyboard"});
}

void set_led_state(LedState state) {
  ps2_register.put_byte(0xed);
  ps2_register.put_byte((uint8_t)state);
  AWAIT_RESPONSE();
  // if (response != Response::Acknoledged) {
  //   // todo: should propagate error to caller
  //   VgaDisplay::put_string(KS::StringView("cannot set LED state"));
  // }
}

}
