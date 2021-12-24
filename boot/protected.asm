[bits 16]
enter_protected_mode:
  cli ; disable interrupt

  lgdt [gdt_descriptor] ; load descriptor table

  mov eax, cr0 ; enable protected mode
  or eax, 0x1
  mov cr0, eax

  jmp CODE_SEG:init_protected_mode ; far jump

[bits 32]
init_protected_mode:
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov esp, 0x90000
  mov ebp, esp

  call protected_mode_entry
