# SOURCE ###############################################################
SRC = main.c getopt.c queue.c Point.c
OBJ = $(SRC:.c=.o)

# PROGRAMS #############################################################
CC = gcc
RM = rm -f

# DIRECTORIES ##########################################################
LDLIBS = -L.
CLIBS = -I.
BIN = bin

# FLAGS ################################################################
CFLAGS = -g -ansi -Wall -pedantic -O2
LDFLAGS = -lm

# TARGETS ##############################################################
conectivity: $(OBJ)
	$(CC) $^ -o $(BIN)/$@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $^

clean:
	$(RM) *.o *.gch *~
