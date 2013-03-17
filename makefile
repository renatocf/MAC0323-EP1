CC=gcc
CFLAGS=-ansi -Wall -pedantic -O2
BIN=bin

RM=rm -f
RMARGS=*.o *.gch

conectivity: main.o getopt.o queue.o
	$(CC) $^ -o $(BIN)/$@
	# @ $(RM) $(RMARGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $^

getopt.o: getopt.c getopt.h
	$(CC) $(CFLAGS) -c $^

queue.o: queue.c queue.h Item.h
	$(CC) $(CFLAGS) -c $^

.PHONY: GDB
GDB: main.o getopt.o queue.o
	$(CC) $(CFLAGS) -g $^ -o $@

clean:
	$(RM) $(RMARGS)
