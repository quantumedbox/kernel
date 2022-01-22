#pragma once

#include <stdint.h>

namespace CPU
{

typedef struct {
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} RegisterDump; 

typedef struct {
  // data sector selector
  uint32_t ds;
  RegisterDump registers;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} CpuState;

RegisterDump dump_registers();

inline void interrupt(uint8_t code) {
  asm volatile("int %0" : : "i" (code));
}

inline void enable_interrupts() {
  asm volatile("sti");
}

inline void disable_interrupts() {
  asm volatile("cli");
}

}
