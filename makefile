balance: main.o files.o interface.o
	gcc -o balance main.o files.o interface.o

main.o: src/main.c src/files.h src/interface.h
	gcc -c src/main.c

files.o: src/files.c src/files.h
	gcc -c src/files.c

interface.o: src/interface.c src/interface.h
	gcc -c src/interface.c


