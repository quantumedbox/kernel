CXX := g++
shared_args := -ffreestanding -nostdlib -I $(CURDIR)
io_dir := ./io
display_dir := ./display

.PHONY: clean run

all: entry.o kernel.a

entry.o: entry.cpp
	$(CXX) -m32 -c $< $(shared_args) -Os -o _tmp$@
	objcopy -O elf32-i386 _tmp$@ $@

kernel.a: io.o display.o
	ar cr $@ $^

io.o: $(io_dir)/port.cpp
	$(CXX) -m32 -c $< $(shared_args) -O3 -o $@

display.o: $(display_dir)/display.cpp
	$(CXX) -m32 -c $< $(shared_args) -O3 -o $@

clean:
	$(RM) *.a *.o
