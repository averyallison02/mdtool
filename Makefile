CC = clang

main: bin/mdtool

bin/mdtool: src/prompt.c
	$(CC) -g -o bin/mdtool src/prompt.c
