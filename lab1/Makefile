%.o: %.c
	gcc -c -o $@ $<

all: banana

banana : invert.o
	cc -o $@ $^

invert.o: invert.c
	cc -c $<

clean :
	rm -f *.o