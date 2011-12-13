%.o: %.asm
	nasm -g -f elf -o $@ $<

.PHONY: clean all

all: check_equal

check_equal: check_equal.o hsvmhr.o
	gcc -m32 -o $@ $^

check_equal.o: check_equal.c
	gcc -m32 -c -o $@ $^

clean:
	rm *.o check_equal
