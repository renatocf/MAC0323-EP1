# SOURCE ###############################################################
SRC = queue.c main.c getopt.c Point.c
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

# PROGRAMS #############################################################
CC = gcc
RM = rm -f

# DIRECTORIES ##########################################################
VPATH = queue
CLIBS = -Iqueue
LDLIBS = -L. 
BIN = bin

# FLAGS ################################################################
CFLAGS = -g -ansi -Wall -pedantic -O2
LDFLAGS = -lm

# TARGETS ##############################################################

# all:
# 	echo $(SRC)
# 	echo $(OBJ)

conectivity: $(OBJ)
	$(CC) $^ -o $(BIN)/$@ $(LDFLAGS)

$(OBJ): | obj

obj:
	echo $(OBJ)
	mkdir -p $@

obj/%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $^ -o $@

clean:
	$(RM) obj/*.o
