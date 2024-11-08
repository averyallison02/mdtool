CC = gcc

default: bin/mdtool

bin/mdtool: src/mdtool.c
	$(CC) -g -o bin/mdtool src/mdtool.c
