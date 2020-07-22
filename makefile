balance: main.o balance.o interface.o files.o
	gcc -o balance main.o balance.o interface.o files.o

main.o: src/main.c src/balance.h src/interface.h src/files.h
	gcc -c src/main.c

balance.o: src/balance.c src/balance.h
	gcc -c src/balance.c

interface.o: src/interface.c src/interface.h
	gcc -c src/interface.c

files.o : src/files.c src/files.h
	gcc -c src/files.c


