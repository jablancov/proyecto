PROG = main

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

${PROG}: ${PROG}.c
	${CC} ${CFLAGS} -o exe_p1 ${PROG}.c ${LIBS}

clean:
	rm exe_p1