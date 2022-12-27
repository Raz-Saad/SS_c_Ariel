CC = gcc
FLAGS = -Wall

all: isort txtfind

isort: isort.o
	$(CC) $(FLAGS) isort.o -o isort

isort.o:isort.c
	$(CC) $(FLAGS) -c isort.c

txtfind: txtfind.o
	$(CC) $(FLAGS) txtfind.o -o txtfind

txtfind.o: txtfind.c
	$(CC) $(FLAGS) -c txtfind.c

.PHONY: clean all 

clean:
	rm -f *.o isort txtfind
