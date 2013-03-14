CC=gcc
CFLAGS=-ansi -Wall -pedantic -O2
BIN=bin

RM=rm -f

conectivity: main.o
	$(CC) $^ -o $(BIN)/$@
	@ $(RM) *.o

main.o: main.c
	$(CC) $(CFLAGS) -c $^

.PHONY: GDB
GDB: main.o
	$(CC) $(CFLAGS) -g $^ -o $@
