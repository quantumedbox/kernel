#pragma once

#include <stdint.h>

typedef struct {
  size_t len;
  uint8_t* chars;
} String;

#define string_from_literal(str) (String){ sizeof(str), (uint8_t*)str }
#define init_string(str, _len) (String){ (_len), (str) }
