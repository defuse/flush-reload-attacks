OBJS=mem.o spy.o config.o
PROG=spy
CFLAGS=-g -std=gnu99 -O2
LOADLIBES= -lm

all: ${PROG}


spy: spy.o mem.o config.o

spy.o: mem.h config.h

mem.o: mem.h

config.o: config.h

clean: 
	rm -f ${PROG} ${OBJS}
