CC=gcc
CFLAGS=-ansi -Wall -pedantic -O2
LDFLAGS=-lm
BIN=bin

RM=rm -f
RMARGS=*.o *.gch

conectivity: main.o getopt.o queue.o Point.o
	$(CC) $^ -o $(BIN)/$@ $(LDFLAGS)
	# @ $(RM) $(RMARGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $^

getopt.o: getopt.c getopt.h
	$(CC) $(CFLAGS) -c $^

queue.o: queue.c queue.h queue-internal.h Item.h
	$(CC) $(CFLAGS) -c $^

Point.o: Point.c Point.h
	$(CC) $(CFLAGS) -c $^

.PHONY: GDB
GDB: main.o getopt.o queue.o
	$(CC) $(CFLAGS) -g $^ -o $@

clean:
	$(RM) $(RMARGS)
