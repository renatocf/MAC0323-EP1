CC=gcc
CFLAGS=-ansi -Wall -pedantic -O2
BIN=bin

hipo_assembler: main.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@
