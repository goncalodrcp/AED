CC=gcc
CFLAGS=-g -Wall

Burster: main.o list.o puzzle.o utils.o
	$(CC) $(CFLAGS) -o Burster main.o list.o utils.o puzzle.o

main.o: main.c list.h puzzle.h utils.h
	$(CC) -c $(CFLAGS) main.c

puzzle.o: puzzle.c puzzle.h utils.h defs.h
	$(CC) -c $(CFLAGS) puzzle.c

list.o: list.c list.h utils.h puzzle.h defs.h
	$(CC) -c $(CFLAGS) list.c

utils.o: utils.c utils.h defs.h list.h puzzle.h
	$(CC) -c $(CFLAGS) utils.c

clean::
	    rm -f *.o core a.out Burster *~
