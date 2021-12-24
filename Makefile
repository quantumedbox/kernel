CXX := g++

boot_src_dir = ./boot
kernel_src_dir = ./kernel

.PHONY: clean run

all: run

kernel.bin: kernel_entry.o $(kernel_src_dir)/entry.o
	ld -mi386pe -T NUL -o _tmp$@ -Ttext 0x1000 $^
	objcopy -O binary -j .text _tmp$@ $@

kernel_entry.o: $(boot_src_dir)/kernel_entry.asm
	nasm $< -f elf32 -o $@

boot.bin: $(boot_src_dir)/boot.asm
	nasm $< -f bin -o $@ -I $(boot_src_dir)

$(kernel_src_dir)/entry.o | $(kernel_src_dir)/kernel.a:
	$(MAKE) -C $(kernel_src_dir)

os-image.bin: boot.bin kernel.bin $(kernel_src_dir)/kernel.a
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -fda $<

clean:
	$(RM) *.bin *.o *.dis _tmp*.*
	$(MAKE) -C $(kernel_src_dir) clean
