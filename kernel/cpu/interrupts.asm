BITS 32
extern isr_handler
extern irq_handler

isr_handler_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  push esp
  call isr_handler
  pop eax

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa
  ; erase int_no and err_code from stack
  add esp, 8
  ; sti
  iret

irq_handler_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  push esp
  call irq_handler
  pop eax

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa
  ; erase int_no and err_code from stack
  add esp, 8
  ; sti
  iret

%macro generic_isr_definition 1
  global isr%1
isr%1:
  ; cli
  push byte 0
  push byte %1
  jmp isr_handler_stub
%endmacro

%macro generic_irq_definition 1
  global irq%1
irq%1:
  ; cli
  push byte %1
  push byte 32 + %1
  jmp irq_handler_stub
%endmacro

generic_isr_definition 0
generic_isr_definition 1
generic_isr_definition 2
generic_isr_definition 3
generic_isr_definition 4
generic_isr_definition 5
generic_isr_definition 6
generic_isr_definition 7
generic_isr_definition 8
generic_isr_definition 9
generic_isr_definition 10
generic_isr_definition 11

; special case on stack fault as it does pushes information
global isr12
isr12:
  push byte 12
  jmp isr_handler_stub

generic_isr_definition 13
generic_isr_definition 14
generic_isr_definition 15
generic_isr_definition 16
generic_isr_definition 17
generic_isr_definition 18
generic_isr_definition 19
generic_isr_definition 20
generic_isr_definition 21
generic_isr_definition 22
generic_isr_definition 23
generic_isr_definition 24
generic_isr_definition 25
generic_isr_definition 26
generic_isr_definition 27
generic_isr_definition 28
generic_isr_definition 29
generic_isr_definition 30
generic_isr_definition 31

generic_irq_definition 0
generic_irq_definition 1
generic_irq_definition 2
generic_irq_definition 3
generic_irq_definition 4
generic_irq_definition 5
generic_irq_definition 6
generic_irq_definition 7
generic_irq_definition 8
generic_irq_definition 9
generic_irq_definition 10
generic_irq_definition 11
generic_irq_definition 12
generic_irq_definition 13
generic_irq_definition 14
generic_irq_definition 15
