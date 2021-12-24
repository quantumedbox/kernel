#include "inttypes.h"

namespace Display {

void set_cursor(int32_t offset);
int32_t get_cursor();
void set_char(uint8_t character, int32_t offset);

}
