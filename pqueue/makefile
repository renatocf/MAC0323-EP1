SRC = teste.c pqueue.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -ansi -Wall -pedantic -g

RM = rm -f

teste: $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o ~*
