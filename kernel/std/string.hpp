#pragma once

#include <stdint.h>
#include <stddef.h>

// todo: it's possible to create string literals objects without them storing their size
//       we might just separate such strings from others, tho is there a real need?

namespace KS {

/*
  String view class used in kernel for passing rodata strings and such
*/
class StringView {
  const uint8_t* chars;
  const size_t len;

public:

  /*
    Should be used for defining compile-time string object from C-style string literals
    One side effect of this is that such strings have NULL terminator attached to them at the end

    to consider: should NULL be included in len? or we must ensure that all strings, even the ones created
                 at runtime should always have NULL at the end?
                 or should it be just a valid part of data without ensuring anything
  */
  template<size_t len>
  constexpr StringView(const char (&str) [len])
    : chars ((uint8_t*)&str)
    , len (len)
  {
  }

  StringView(const uint8_t* str, size_t len)
    : chars (str)
    , len (len)
  {
  }

  size_t get_len() const { return len; }
  const uint8_t* get_view() const { return chars; }

};

}
