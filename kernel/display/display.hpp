#include "inttypes.h"

namespace Display {

void set_cursor(int32_t offset);
uint32_t get_cursor();
void put_char(uint8_t character, uint32_t offset);
void clear_screen();

}
