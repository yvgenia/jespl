# generic rule for compiling C files

CFLAGS=-g -O -Wall

%.o: %.c
	gcc -c $(CFLAGS) -o $@ $<

%: %.o
	gcc $(CFLAGS) -o $@ $<

all: elfheader

esplsh: elfheader.o

clean:
	rm -f *.o

distclean: clean
	rm -f elfheader *~
