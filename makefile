CC=gcc
CFLAGS=-ansi -Wall -pedantic -O2
PATH=bin
RM=rm -f

conexidade: main.o
	$(CC) $^ -o $(PATH)/$@
	@ $(RM) *.o

main.o: main.c
	$(CC) $(CFLAGS) -c $^
