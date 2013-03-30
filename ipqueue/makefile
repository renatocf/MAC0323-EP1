SRC = teste2.c krustal.c pltree.c ipqueue.c
OBJ = $(SRC:.c=.o)

CFLAGS=-g -I. -ansi -Wall -pedantic
LDFLAGS=-lm
LDLIBS=-L.

CC=gcc
RM=rm -f

teste2: $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *~ *.gch
