SOURCES=utils.c main.c
CC=gcc
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-fopenmp -c
LDFLAGS=-fopenmp

all: prog





prog: ${OBJECTS}
	        ${CC} ${LDFLAGS} ${OBJECTS} -o $@

.c.o:
	        ${CC} ${CFLAGS} $<
clean:
	        @rm -fv *.o prog
