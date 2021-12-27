CXX := i686-elf-g++
CXX_SOURCES = $(wildcard ./kernel/*.cpp ./kernel/cpu/*.cpp ./kernel/io/*.cpp ./kernel/display/*.cpp)
OBJ = ${CXX_SOURCES:.cpp=.o kernel/cpu/interrupts.o}

CXXFLAGS := -ffreestanding -nostdlib -g -Wall -Wextra -Os -fno-exceptions -fno-rtti
log_name := "log.txt"

.PHONY: clean run debug

os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin: boot/kernel_entry.o $(OBJ)
	i686-elf-ld -m elf_i386 -T link.ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o $(OBJ)
	i686-elf-ld -o $@ -Ttext 0x1000 $^

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ -I ./kernel/

%.o: %.asm
	nasm $< -f elf32 -o $@ -I ./boot/

%.bin: %.asm
	nasm $< -f bin -o $@ -I ./boot/

run: os-image.bin
	qemu-system-i386 -drive format=raw,file=$< -serial file:$(log_name)

debug: os-image.bin
	qemu-system-i386 -s -S -drive format=raw,file=$< -serial file:$(log_name) &
	i686-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.bin"

clean:
	find ./ -type f -name '*.bin' -exec rm {} +
	find ./ -type f -name '*.o' -exec rm {} +
	$(RM) *.dis _tmp*.* *.elf *.sym $(log_name)
