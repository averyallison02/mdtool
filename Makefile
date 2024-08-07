CC = clang

main: bin/mdtool

bin/mdtool: src/prompt.c
	$(CC) -o bin/mdtool src/prompt.c
