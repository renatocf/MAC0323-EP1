CC := gcc
CFLAGS := -ansi -Wall -pedantic -g -I.
RM := rm -f

VPATH = ../obj
ODIR = ../obj

$(LIB).o: $(LIB).c $(HEADERS)
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $(ODIR)/$@

clean:
	$(RM) $(ODIR)/$(LIB).o
