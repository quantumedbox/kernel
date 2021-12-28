ENTRY(_entry)
/*OUTPUT_FORMAT(elf_32)*/
KERNEL_OFFSET = 0x1000;

SECTIONS {

  . = KERNEL_OFFSET;

  __kernel_base = .;

  .text BLOCK(4K) : ALIGN(4K) {
    __text_start = .;
    *(.multiboot)
    *(.text)
    __text_end = .;
  }

  .rodata BLOCK(4K) : ALIGN(4K) {
    __rodata_start = .;
    *(.rodata)
  }

  .data BLOCK(4K) : ALIGN(4K) {
    __data_start = .;
    *(.data)
  }

  .bss BLOCK(4K) : ALIGN(4K) {
    __bss_start = .;
    *(.bss)
    __bss_end = .;
    *(COMMON)
  }

  /DISCARD/ :
  {
    *(.fini_array*)
    *(.note.*)
    *(.eh_frame*)
    *(.comment)
  }

  __end = .;

}
