CXX := g++
shared_args := -ffreestanding -nostdlib -I $(CURDIR)
io_dir := ./io
display_dir := ./display

.PHONY: clean run

all: entry.o io.o display.o

entry.o: entry.cpp
	$(CXX) -m32 -c $< $(shared_args) -Os -o $@

io.o: $(io_dir)/port.cpp
	$(CXX) -m32 -c $< $(shared_args) -Os -o $@

display.o: $(display_dir)/display.cpp
	$(CXX) -m32 -c $< $(shared_args) -Os -o $@

clean:
	$(RM) *.a *.o
