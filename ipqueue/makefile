CFLAGS=-g -I. -ansi -Wall -pedantic
LDFLAGS=-lm
LDLIBS=-L.

CC=gcc
RM=rm -f

teste: ipqueue.o pltree.o teste.o
	$(CC) $^ -o $@ $(LDLIBS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *~ *.gch
