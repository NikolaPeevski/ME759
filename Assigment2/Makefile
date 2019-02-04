CC = gcc
CCP = g++
CFLAGS = -std=c99 -g

#problem1.o instead of problem1 for make clean to work

problem: problem1a problem1b problem2a

problem1a: problem1a.c
	$(CC) $(CFLAGS) problem1a.c -o problem1a

problem1b: problem1b.c
	$(CC) $(CFLAGS) problem1b.c -o problem1b

problem2a: problem2a.c
	$(CC) $(CFLAGS) problem2a.c -o problem2a

clean:
	rm -rf *.o
	rm -rf *.o.dSYM
