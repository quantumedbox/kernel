extern kernel_entry

MAGIC_NUMBER equ 0x1BADB002
PAGE_ALIGN_FLAG equ   1 << 0
MEMORY_INFO_FLAG equ  1 << 1
GRAPHICS_FLAG equ     1 << 2
HEADER_FLAG equ MEMORY_INFO_FLAG ; | GRAPHICS_FLAG

section .multiboot
align 4
magic dd MAGIC_NUMBER
flag dd HEADER_FLAG
checksum dd -(MAGIC_NUMBER + HEADER_FLAG)

; ELF tag
; dd 0 ; num
; dd 1024 ; size
; dd 728 ; addr
; dd 32 ; shndx

; dd 0 ; '0' for graphics mode, '1' for text, tho there's no guarantee
; dd 800 ; width in pixels or columns
; dd 680 ; height in pixels or lines
; dd 16 ; bits per pixel aka 'depth', 0 stands for no preference

section .bss
align 16 ; stack should be always aligned to 16 bit boundary as it's assumed
stack_bottom:
resb 16384
stack_top:

section .text
global _entry
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

  ; specify text mode 0x02
  ; mov ah, 0x00
  ; mov al, 0x02
  ; int 0x10

  call kernel_entry

  cli ; turn off interrupts
.inf:
  hlt ; send interrupt which will never be dispatched (hopefully)
  jmp .inf ; infinite loop in case of non-maskable interrupt

%include "boot/32bit_print.asm"

; KERNEL_LOADING_MSG db "loading kernel...", 0
