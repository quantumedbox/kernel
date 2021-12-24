
; bx -> output buffer
; dh -> n of sectors
; dl -> drive
load_disk:
  pusha ; todo: is it really necessary to push all registers?
  push dx

  mov ah, 0x02 ; read mode
  mov al, dh   ; dh count of sectors
  mov cl, 0x02 ; start from second sector, 0x01 is boot sector
  mov ch, 0x00
  mov dh, 0x00

  int 0x13 ; bios interrupt
  jc disk_error ; short circuit on error, as interrupt sets carry flag on error

  pop dx
  cmp al, dh ; al is set to count of sectors read
  jne disk_error

  popa
  ret

disk_error:
  jmp $
