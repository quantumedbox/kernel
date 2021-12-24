[bits 16]
[org 0x7c00]

  ; point at which BIOS gives control

  ; memory location to which kernel will be loaded
  KERNEL_OFFSET equ 0x1000

  ; store current drive, we will read kernel from the same drive as boot one
  mov [BOOT_DRIVE], dl

  ; initialize stack at 0x9000
  mov sp, 0x9000 ; stack pointer
  mov bp, sp    ; base pointer

  call load_kernel
  call enter_protected_mode

  jmp $ ; catcher

%include "disk.asm"
%include "gdt.asm"
%include "protected.asm"

[bits 16]
load_kernel:
  mov bx, KERNEL_OFFSET
  mov dh, 2
  mov dl, [BOOT_DRIVE]
  call load_disk
  ret

[bits 32]
protected_mode_entry:
  call KERNEL_OFFSET ; jump to kernel
  jmp $

BOOT_DRIVE db 0

; padding
times 510 - ($-$$) db 0

; signature
dw 0xaa55
