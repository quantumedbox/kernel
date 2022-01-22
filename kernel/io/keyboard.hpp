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

void init();

/*
  @brief  Dispatches internal buffer of scancodes to gettable queue of implementation independent keycodes
  @warn   Shouldn't be used by anything but internal loop
*/
void process();


void set_led_state(LedState state);

}
