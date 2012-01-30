%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g  -c -o $@ $<

.PHONY: clean all

all: ascart

ascart: ascart.o font.o functions.o
#ascart: asmart.o ascart.o font.o functions.o
	gcc -m32 -g -o $@ $^

#	ld -melf_i386 -g -o $@ $^



ascart.o: ascart.c
font.o: font.c font.h
asmart.o: asmart.asm


clean:
	rm *.o ascart
	
	
