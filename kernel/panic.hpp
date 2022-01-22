#pragma once

#include "std/string.hpp"

namespace KS
{
  [[noreturn]] void panic(const StringView);

  void assert(bool, const StringView);

  inline void infinite_loop() {
    while (1) { __asm__ ("hlt"); }
  }
}
