/*
  Header which 
  Mush be 64-bit aligned and placed in the first 32KB of memory 
*/

// todo:

#include <stdint.h>

struct multiboot_header {
  uint32_t magic_number;
  uint32_t architecture;
  uint32_t header_length;
  uint32_t checksum;
} __attribute__((section(".multiboot")));

struct multiboot_header header = {
  0xE85250D6,
  0,


};
