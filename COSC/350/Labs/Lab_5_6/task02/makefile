# Makefile created by Thomas Pearson on 2/21/2024
PROG = prog
CC = gcc
CFLAGS = -g -Wall
OBJS = task2.o

${PROG} : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o :
	$(CC) $(CFLAGS) -c task2.c

clean :
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
