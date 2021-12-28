#include "ldt.hpp"
#include "io/port.hpp"
#include "display/display.hpp"
#include "std/string.hpp"
#include "memory.h"

namespace CPU {

typedef struct {
  uint16_t low_offset;
  uint16_t selector;
  uint8_t zero_segment;
  uint8_t flags;
  uint16_t high_offset;
} __attribute__((packed)) LdtGate;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) LdtDescriptor;

#define N_LDT_GATES 256
#define N_RESERVED_IDT_EXCEPTIONS 32

__attribute__((aligned(0x10)))
static LdtGate ldt[N_LDT_GATES];
static InterruptHandler interrupt_handlers[N_LDT_GATES];
static LdtDescriptor ldt_descriptor;

constexpr IO::Port PIC1_command_port { 0x20 };
constexpr IO::Port PIC1_data_port { 0x21 };
constexpr IO::Port PIC2_command_port { 0xa0 };
constexpr IO::Port PIC2_data_port { 0xa1 };

static void idt_load() {
  ldt_descriptor.base = (uint32_t)&ldt;
  ldt_descriptor.limit = N_LDT_GATES * sizeof(LdtDescriptor) - 1;
  asm volatile("lidt (%0)" : : "m" (ldt_descriptor));
}

void set_ldt_gate(uint8_t idx, uint32_t handler) {
  ldt[idx].low_offset = LOW_16(handler);
  ldt[idx].selector = 0x08;
  ldt[idx].zero_segment = 0;
  ldt[idx].flags = 0x8e; // todo: pass flags externally
  ldt[idx].high_offset = HIGH_16(handler);
}

// todo: check handle address validity
void register_interrupt_handler(uint8_t idx, InterruptHandler handler) {
  interrupt_handlers[idx] = handler;
}

// constexpr KS::String exception_messages[N_RESERVED_IDT_EXCEPTIONS] = {
//   KS::String("div by 0"),
//   KS::String("-- single-step interrupt"),
//   KS::String("-- non-maskable interrupt"),
//   KS::String("-- breakpoint"),
//   KS::String("overflow"),
//   KS::String("bound range exceeded"),
//   KS::String("invalid opcode"),
//   KS::String("coprocessor not available"),
//   KS::String("double fault"),
//   KS::String("invalid task state segment"),
//   KS::String("segment not present"),
//   KS::String("stack segment fault"),
//   KS::String("-- general protection fault"),
//   KS::String("page fault"),
//   KS::String("-- reserved interrupt"),
//   KS::String("floating point exception"),
//   KS::String("alignment check"),
//   KS::String("machine check"),
//   KS::String("simd floating point exception"),
//   KS::String("virtualization exception"),
//   KS::String("control protection exception")
// };

extern "C" void isr_handler(Registers* r) {
  // VgaDisplay::put_string(exception_messages[r->int_no]);
  // VgaDisplay::newline_offset();
}

extern "C" void irq_handler(Registers* r) {
  if (r->int_no >= IRQ8)
    PIC2_command_port.put_byte(0x20);
  PIC1_command_port.put_byte(0x20);

  InterruptHandler handler = interrupt_handlers[r->int_no];
  if (handler != (InterruptHandler)0)
    handler(r);
}

void idt_init() {
  set_ldt_gate(0, (uint32_t)isr0);
  set_ldt_gate(1, (uint32_t)isr1);
  set_ldt_gate(2, (uint32_t)isr2);
  set_ldt_gate(3, (uint32_t)isr3);
  set_ldt_gate(4, (uint32_t)isr4);
  set_ldt_gate(5, (uint32_t)isr5);
  set_ldt_gate(6, (uint32_t)isr6);
  set_ldt_gate(7, (uint32_t)isr7);
  set_ldt_gate(8, (uint32_t)isr8);
  set_ldt_gate(9, (uint32_t)isr9);
  set_ldt_gate(10, (uint32_t)isr10);
  set_ldt_gate(11, (uint32_t)isr11);
  set_ldt_gate(12, (uint32_t)isr12);
  set_ldt_gate(13, (uint32_t)isr13);
  set_ldt_gate(14, (uint32_t)isr14);
  set_ldt_gate(15, (uint32_t)isr15);
  set_ldt_gate(16, (uint32_t)isr16);
  set_ldt_gate(17, (uint32_t)isr17);
  set_ldt_gate(18, (uint32_t)isr18);
  set_ldt_gate(19, (uint32_t)isr19);
  set_ldt_gate(20, (uint32_t)isr20);
  set_ldt_gate(21, (uint32_t)isr21);
  set_ldt_gate(22, (uint32_t)isr22);
  set_ldt_gate(23, (uint32_t)isr23);
  set_ldt_gate(24, (uint32_t)isr24);
  set_ldt_gate(25, (uint32_t)isr25);
  set_ldt_gate(26, (uint32_t)isr26);
  set_ldt_gate(27, (uint32_t)isr27);
  set_ldt_gate(28, (uint32_t)isr28);
  set_ldt_gate(29, (uint32_t)isr29);
  set_ldt_gate(30, (uint32_t)isr30);
  set_ldt_gate(31, (uint32_t)isr31);

  PIC1_command_port.put_byte(0x11);
  PIC2_command_port.put_byte(0x11);

  PIC1_data_port.put_byte(0x20);
  PIC2_data_port.put_byte(0x28);

  PIC1_data_port.put_byte(0x04);
  PIC2_data_port.put_byte(0x02);

  PIC1_data_port.put_byte(0x01);
  PIC2_data_port.put_byte(0x01);

  PIC1_data_port.put_byte(0x00);
  PIC2_data_port.put_byte(0x00);

  // primary PIC interrupt requests
  set_ldt_gate(32, (uint32_t)irq0);
  set_ldt_gate(33, (uint32_t)irq1);
  set_ldt_gate(34, (uint32_t)irq2);
  set_ldt_gate(35, (uint32_t)irq3);
  set_ldt_gate(36, (uint32_t)irq4);
  set_ldt_gate(37, (uint32_t)irq5);
  set_ldt_gate(38, (uint32_t)irq6);
  set_ldt_gate(39, (uint32_t)irq7);

  // secondary PIC interrupt requests
  set_ldt_gate(40, (uint32_t)irq8);
  set_ldt_gate(41, (uint32_t)irq9);
  set_ldt_gate(42, (uint32_t)irq10);
  set_ldt_gate(43, (uint32_t)irq11);
  set_ldt_gate(44, (uint32_t)irq12);
  set_ldt_gate(45, (uint32_t)irq13);
  set_ldt_gate(46, (uint32_t)irq14);
  set_ldt_gate(47, (uint32_t)irq15);

  idt_load();
}

}
