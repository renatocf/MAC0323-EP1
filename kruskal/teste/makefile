SRC = teste.c kruskal.c pltree.c ipqueue.c
OBJ = $(patsubst %.c,%.o,$(SRC))

CFLAGS=-g -ansi -Wall -pedantic
CLIBS = -I. -I.. -I../../ipqueue -I../../pltree -I../../edge -I../../ \
		-I../../Point

VPATH=..:../../Point:../../ipqueue:../../pltree:../../edge

CC=gcc
RM=rm -f

teste: $(OBJ)
	@echo $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS) $(LDFLAGS)

%.o: %.c
	@ $(CC) $(CLIBS) $(CFLAGS) -c $^

clean:
	$(RM) *.o *~ *.gch
