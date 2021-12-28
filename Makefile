CXX := i686-elf-g++
CXX_SOURCES = $(wildcard ./kernel/*.cpp ./kernel/cpu/*.cpp ./kernel/io/*.cpp ./kernel/display/*.cpp)
OBJ = ${CXX_SOURCES:.cpp=.o kernel/cpu/interrupts.o}

CXXFLAGS := -ffreestanding -nostdlib -g -Wall -Wextra -Os -fno-exceptions -fno-rtti
log_name := "log"

.PHONY: clean run debug

# os-image.bin: boot/bootsect.bin kernel.bin
# 	cat $^ > $@

os-image.bin: os-image.elf
	objcopy -S $< $@

os-image.elf: boot/multiboot1/entry.o boot/kernel_entry.o $(OBJ)
	i686-elf-ld -T link.ld -o $@ $^

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ -I ./kernel/ -I ./boot/

%.o: %.asm
	nasm $< -f elf32 -o $@ -I ./boot/

%.bin: %.asm
	nasm $< -f bin -o $@ -I ./boot/

run: os-image.bin
	qemu-system-i386 -kernel $< -serial file:$(log_name)

debug: os-image.elf
	qemu-system-i386 -s -kernel $< -serial file:$(log_name) &
	gdb -ex "target remote localhost:1234" -ex "symbol-file os-image.elf" -ex "b kernel_entry" -ex "c"

clean:
	find ./ -type f -name '*.bin' -exec rm {} +
	find ./ -type f -name '*.o' -exec rm {} +
	$(RM) *.dis _tmp*.* *.elf *.sym $(log_name)
