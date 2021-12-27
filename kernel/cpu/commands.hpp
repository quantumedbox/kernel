
namespace CPU {

inline void interrupt(uint8_t code) {
  asm volatile("int %0" : : "n" (code));
}

inline void enable_interrupts() {
  asm volatile("sti");
}

inline void disable_interrupts() {
  asm volatile("cli");
}

}
