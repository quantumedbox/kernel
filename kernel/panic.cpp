#include "panic.hpp"
#include "display/display.hpp"
#include "cpu/ldt.hpp"

static constexpr VgaDisplay::StyleAttribute panic_style = VgaDisplay::init_style<VgaDisplay::Color::Red, VgaDisplay::Color::Black>();

namespace KS
{

  // void panic_handler(CpuState*)
  // {

  // }

  [[noreturn]] void panic(const StringView msg)
  {
    VgaDisplay::set_style(panic_style);
    VgaDisplay::fill_screen(' ');
    VgaDisplay::set_offset(0);
    VgaDisplay::put_string(StringView{"----------- Kernel panic! -----------"});
    VgaDisplay::newline_offset();
    VgaDisplay::put_string(msg);
    VgaDisplay::newline_offset();

    // todo: find a way to get unaffected register dumb and text message at the same time

    // VgaDisplay::put_string(StringView{"----------- Register Dump -----------"});
    // VgaDisplay::newline_offset();
    // CPU::RegisterDump registers = CPU::dump_registers();
    // VgaDisplay::put_string(StringView{"EAX: "});
    // VgaDisplay::put_uint32(registers.eax);
    // VgaDisplay::newline_offset();
    // VgaDisplay::put_string(StringView{"EBX: "});
    // VgaDisplay::put_uint32(registers.ebx);
    // VgaDisplay::newline_offset();
    // VgaDisplay::put_string(StringView{"ECX: "});
    // VgaDisplay::put_uint32(registers.ecx);
    // VgaDisplay::newline_offset();
    // VgaDisplay::put_string(StringView{"EDX: "});
    // VgaDisplay::put_uint32(registers.edx);
    // VgaDisplay::newline_offset();
    // VgaDisplay::put_string(StringView{"EBP: "});
    // VgaDisplay::put_uint32(registers.ebp);
    // VgaDisplay::newline_offset();
    // VgaDisplay::put_string(StringView{"ESP: "});
    // VgaDisplay::put_uint32(registers.esp);
    // VgaDisplay::newline_offset();

    infinite_loop();
  }

  // todo: make it debug build exclusive
  void assert(bool expr, const StringView msg) {
    if (!expr)
      panic(msg);
  }

}
