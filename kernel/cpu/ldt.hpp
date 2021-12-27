/*
  Local Descriptor Table functionalities for 8086 CPUs
*/

// todo: rename to idt.hpp? as it not only deals with local interrupts

#pragma once

#include <stdint.h>

namespace CPU {

enum {
  IRQ0 = 32, // system timer
  IRQ1, // keyboard interrupt
  IRQ2, // cascaded signals from second PIC, shouldn't be raised
  IRQ3, // serial port controller 2 / 4
  IRQ4, // serial port controller 1 / 3
  IRQ5, // parralel port 3 or sound card
  IRQ6, // floppy disk controller
  IRQ7, // parallel port 1 / 2
  IRQ8, // real-time clock
  IRQ9,
  IRQ10,
  IRQ11,
  IRQ12, // free to use for peripherals
  IRQ13, // free to use for peripherals
  IRQ14, // primary ATA channel
  IRQ15  // secondary ATA channel
};

typedef struct {
  // data sector selector
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} Registers;

typedef void (*InterruptHandler)(Registers*);

void idt_init();
void set_ldt_gate(uint8_t idx, uint32_t hadler);
void register_interrupt_handler(uint8_t idx, InterruptHandler);

extern "C" {
  void isr_handler(Registers*);
  void irq_handler(Registers*);

  extern void isr0();
  extern void isr1();
  extern void isr2();
  extern void isr3();
  extern void isr4();
  extern void isr5();
  extern void isr6();
  extern void isr7();
  extern void isr8();
  extern void isr9();
  extern void isr10();
  extern void isr11();
  extern void isr12();
  extern void isr13();
  extern void isr14();
  extern void isr15();
  extern void isr16();
  extern void isr17();
  extern void isr18();
  extern void isr19();
  extern void isr20();
  extern void isr21();
  extern void isr22();
  extern void isr23();
  extern void isr24();
  extern void isr25();
  extern void isr26();
  extern void isr27();
  extern void isr28();
  extern void isr29();
  extern void isr30();
  extern void isr31();

  extern void irq0();
  extern void irq1();
  extern void irq2();
  extern void irq3();
  extern void irq4();
  extern void irq5();
  extern void irq6();
  extern void irq7();
  extern void irq8();
  extern void irq9();
  extern void irq10();
  extern void irq11();
  extern void irq12();
  extern void irq13();
  extern void irq14();
  extern void irq15();
}

}