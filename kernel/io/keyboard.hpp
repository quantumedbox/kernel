/*
  PS/2 IBM compatible keyboard interface
*/

#pragma once

#include <stdint.h>

namespace Keyboard {

using LedState = uint8_t;

template<bool scroll_lock, bool num_lock, bool caps_lock>
constexpr LedState init_led_state() {
  return (LedState)(scroll_lock | (num_lock << 1) | (caps_lock << 2));
}

void init_ps2();
void set_led_state(LedState state);

// todo: move to separate file
// implementation independent keycodes
enum class KeyCode : uint16_t {
  Unknown,
  Esc,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  Tilda,
  One,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Zero,
  Minus,
  Equal,
  Backspace,
  Tab,
  Q,
  W,
  E,
  R,
  T,
  Y,
  U,
  I,
  P,
  OpeningBracket,
  ClosingBracket,
};

}
