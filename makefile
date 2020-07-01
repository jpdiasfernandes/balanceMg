balance: main.o files.o interface.o
	gcc -o balance main.o files.o interface.o

main.o: main.c files.h interface.h
	gcc -c main.c

files.o: files.c files.h
	gcc -c files.c

interface.o: interface.c interface.h
	gcc -c interface.c


