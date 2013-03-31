VPATH = ..

teste: teste.o grid.o
	gcc $^ -o ./$@

%.o: %.c
	gcc -ansi -Wall -pedantic -I.. -I../../Point -g -c $< -o $@
