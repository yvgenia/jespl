.PHONY: all clean

all: calc

calc: calc.o atod.o
	gcc -m32 -o $@ $^

calc.o: calc.c
	gcc -m32 -c -o $@ $^

atod.o: atod.asm
	nasm -g -f elf -o $@ $<
