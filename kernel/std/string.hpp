#pragma once

#include <stdint.h>

namespace KS {

class String {
  const size_t len;
  const uint8_t* chars;

public:

  /*
    Should be used for defining compile-time string object from C-style string literals
    One side effect of this is that such strings have NULL terminator attached to them at the end

    to consider: should NULL be included in len? or we must ensure that all strings, even the ones created
                 at runtime should always have NULL at the end?
                 or should it be just a valid part of data without ensuring anything
  */
  template<size_t len>
  constexpr String(const char (&str) [len])
    : len (len)
    , chars ((uint8_t*)&str)
  {

  }

  String(const uint8_t* str, size_t len)
    : len (len)
    , chars (str)
  {

  }

  size_t get_len() const { return len; }
  const uint8_t* get_view() const { return chars; }

};

}
