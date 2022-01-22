; [org 0x7c00]
; todo: make it extern from linker?
; KERNEL_OFFSET equ 0x1000 ; The same one we used when linking the kernel

extern KERNEL_OFFSET
extern __sectors

global _bootloader_start
[bits 16]
_bootloader_start:
    mov [BOOT_DRIVE], dl ; Remember that the BIOS sets us the boot drive in 'dl' on boot
    mov bp, 0x9000
    mov sp, bp

    xor ax, ax
    mov ds, ax
    mov bx, 0x7c00

    cli
    mov ss, ax
    mov sp, bx
    sti

    ; specify text mode 0x02
    mov ah, 0x00
    mov al, 0x02
    int 0x10

    call load_kernel ; read the kernel from disk
    call switch_to_pm ; disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'
    jmp $ ; Never executed

%include "boot/print.asm"
%include "boot/print_hex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/32bit_print.asm"
%include "boot/switch_pm.asm"
%include "boot/zero_bss.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, __sectors ; Our future kernel will be larger, make this big
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    call zero_bss

    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)


BOOT_DRIVE db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_LOAD_KERNEL db "loading kernel...", 0

; padding
times 510 - ($-$$) db 0
dw 0xaa55
