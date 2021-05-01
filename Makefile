main: buffer.c main.c
	gcc -o main buffer.c main.c -g -Wall -pedantic -lncurses
