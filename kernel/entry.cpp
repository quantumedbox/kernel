#include "io/port.hpp"

extern "C" void kernel_entry() {
  char* video_memory = (char*) 0xb8000;
  *video_memory = 'X';
  *(video_memory + 2) = 'Y';
}
