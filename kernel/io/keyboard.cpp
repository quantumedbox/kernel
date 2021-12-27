#include "keyboard.hpp"

#define SCANCODE_BUFFER_CAPACITY 128

namespace Keyboard {

/*
  All keyboard events should be stored here and then dispatch by specific implementation of dispatcher
*/
uint8_t scancode_buffer[SCANCODE_BUFFER_CAPACITY];

/*
  Initializes interrupt handler at IRQ1 for receiving inputs into the scancode_buffer
*/
void init_PS2() {

}

}
