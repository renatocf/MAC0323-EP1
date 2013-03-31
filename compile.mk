CC = gcc
CFLAGS = -ansi -Wall -pedantic -g -I.
RM = rm -f

ODIR = ../obj

$(LIB).o: $(LIB).c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $(ODIR)/$@

clean:
	$(RM) $(ODIR)/$(LIB).o
