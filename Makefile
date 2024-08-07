CC = clang

bin/mdtool: src/main.c
	$(CC) -o bin/mdtool src/main.c
