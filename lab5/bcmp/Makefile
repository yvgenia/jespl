%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g  -c -o $@ $<

.PHONY: clean all

all: bcmp

bcmp: start.o bcmp.o functions.o
	ld -melf_i386 -g -o $@ $^

bcmp.o: bcmp.c
start.o: start.asm


clean:
	rm *.o bcmp
