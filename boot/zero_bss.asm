extern __bss_start
extern __bss_end

[BITS 32]
zero_bss:
  pusha

  mov edi, __bss_start
  mov ecx, __bss_end
  sub ecx, __bss_start
  mov al, 0
  rep stosb

  popa
  ret
