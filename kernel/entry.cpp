#include "display/display.hpp"
#include <io/port.hpp>

// void print_string(const char *string) {
//   int32_t offset = Display::get_cursor();
//   int32_t i = 0;
//   while (string[i] != 0) {
//     Display::put_char(string[i], offset);
//     i++;
//     offset++;
//   }
//   Display::set_cursor(offset);
// }

extern "C" void kernel_entry() {
  uint8_t* test = (uint8_t*)0xb8000;
  Display::clear_screen();
  test[0] = '!';
  // print_string("hello world");
}
