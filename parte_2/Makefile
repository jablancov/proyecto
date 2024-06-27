# Variables
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
SRC = main.c functions.c

# Targets
all:
	$(CC) $(CFLAGS) -o exe $(SRC) $(LDFLAGS)

clean:
	rm -f *.gp *.dat exe

.PHONY: all clean
