# Variables
CC = gcc
CFLAGS2 = -Wall
LDFLAGS2 = -lm
SRC2 = parte_2/main.c parte_2/functions.c
SRC1 = parte_1/main.c
CFLAGS1 = `pkg-config --cflags gtk+-3.0`
LIBS1 = `pkg-config --libs gtk+-3.0`


# Targets
all: p2 p1

p1:
	${CC} ${CFLAGS1} -o exe_p1 ${SRC1} ${LIBS1}

p2:
	$(CC) $(CFLAGS2) -o exe_p2 $(SRC2) $(LDFLAGS2)

clean:
	rm -f *.gp *.dat exe*

.PHONY: all clean