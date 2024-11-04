CC = clang

default: bin/mdtool

bin/mdtool: bin/prompt.o bin/vault.o
	$(CC) -g -o bin/mdtool bin/prompt.o bin/vault.o

bin/prompt.o: src/prompt.c
	$(CC) -c -g -o bin/prompt.o src/prompt.c

bin/vault.o: src/vault.c
	$(CC) -c -g -o bin/vault.o src/vault.c
