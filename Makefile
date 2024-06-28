# Variables
CC2 = gcc
CFLAGS2 = -Wall
LDFLAGS2 = -lm
SRC2 = parte_2/main.c parte_2/functions.c

# Targets
all: p2

p2:
	$(CC2) $(CFLAGS2) -o exe_p2 $(SRC2) $(LDFLAGS2)

clean:
	rm -f *.gp *.dat exe*

.PHONY: all clean