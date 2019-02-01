CC = gcc
CCP = g++
CFLAGS = -std=c99

#problem1.o instead of problem1 for make clean to work

problem: problem1 problem2 problem3

problem1: problem1.c
	$(CC) $(CFLAGS) problem1.c -o problem1

problem2: problem2.c 
	$(CC) $(CFLAGS) problem2.c -o problem2

problem3: problem3.cpp
	$(CCP) -g problem3.cpp -o problem3

clean:
	rm -rf *.o
	rm -rf *.o.dSYM
