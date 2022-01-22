
#include "x86.hpp"

namespace CPU {

RegisterDump dump_registers()
{
  RegisterDump result;
  asm volatile (
    "movl %%eax, %[a]\n"
    "movl %%ebx, %[b]\n"
    "movl %%ecx, %[c]\n"
    "movl %%edx, %[d]\n"
    "movl %%esp, %[sp]\n"
    "movl %%ebp, %[bp]\n"
    "movl %%edi, %[di]\n"
    "movl %%esi, %[si]"
    :
    [a] "=m" (result.eax), [b] "=m" (result.ebx),
    [c] "=m" (result.ecx), [d] "=m" (result.edx),
    [sp] "=m" (result.esp), [bp] "=m" (result.ebp),
    [di] "=m" (result.edi), [si] "=m" (result.esi)
  );
  return result;
}

}
