/*
  PS/2 IBM compatible keyboard interface
*/

#pragma once

#include <stdint.h>

namespace Keyboard {

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
