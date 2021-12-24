all: run

# todo: make it search for files in project hierarchy

boot_src = ./boot
kernel_src = ./kernel

kernel.bin: kernel_entry.o kernel.o
	ld -mi386pe -T NUL -o _tmp$@ -Ttext 0x1000 $^
	objcopy -O binary -j .text _tmp$@ $@

kernel_entry.o: $(boot_src)/kernel_entry.asm
	nasm $< -f elf32 -o $@

boot.bin: $(boot_src)/boot.asm
	nasm $< -f bin -o $@ -I $(boot_src)

kernel.o: $(kernel_src)/kernel.c
	gcc -m32 -ffreestanding -nostdlib -nostdinc -c -Os $< -o _tmp$@
	objcopy -O elf32-i386 _tmp$@ $@

os-image.bin: boot.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -fda $<

clean:
	$(RM) *.bin *.o *.dis _tmp*.*
