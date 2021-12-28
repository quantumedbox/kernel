extern kernel_entry

MAGIC_NUMBER equ 0x1BADB002
PAGE_ALIGN_FLAG equ   1 << 0
MEMORY_INFO_FLAG equ  1 << 1
HEADER_FLAG equ PAGE_ALIGN_FLAG | MEMORY_INFO_FLAG

section .multiboot
align 4
magic dd MAGIC_NUMBER
flag dd HEADER_FLAG
checksum dd -(MAGIC_NUMBER + HEADER_FLAG)

; ELF tag
dd 0 ; num
dd 1024 ; size
dd 728 ; addr
dd 32 ; shndx

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _entry
; global _entry:function (_start.end - _start)
[bits 32] ; multiboot guarantees that execution will be in protected mode at this point
_entry:
  mov esp, stack_top

  ; reset EFLAGS
  push 0
  popf

  ; second arg - magic number, should be checked by kernel_entry
  push eax
  ; first arg - pointer to multiboot info table
  push ebx

  ; push ebx
  ; mov ebx, KERNEL_LOADING_MSG
  ; call print_string_pm

  ; specify text mode 0x02
  ; mov ah, 0x00
  ; mov al, 0x02
  ; int 0x10

  ; call switch_to_pm

  call kernel_entry

  cli ; turn off interrupts
.inf:
  hlt ; send interrupt which will never be dispatched (hopefully)
  jmp .inf ; infinite loop in case of non-maskable interrupt

; %include "boot/gdt.asm"
%include "boot/32bit_print.asm"

; KERNEL_LOADING_MSG db "loading kernel...", 0
