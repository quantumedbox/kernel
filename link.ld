/*ENTRY(_bios_entry)*/

SECTIONS {
  . = 0x1000;

  .text /*BLOCK(4K)*/ : /*ALIGN(4K)*/ {
    *(.boot)
  }

  .rodata /*BLOCK(4K)*/ : /*ALIGN(4K)*/ {
    *(.rodata)
  }

  .data /*BLOCK(4K)*/ : /*ALIGN(4K)*/ {
    *(.data)
  }

  .bss /*BLOCK(4K)*/ : /*ALIGN(4K)*/ {
    /**(COMMON)*/
    *(.bss)
  }

  /DISCARD/ :
  {
    *(.fini_array*)
    *(.note.*)
    *(.eh_frame*)
    *(.comment)
  }

}
