all: main

main: obj/main.o obj/IntVector.o
	gcc -Wall -O0 -g -o main obj/IntVector.o obj/main.o
obj/main.o: src/main.c
	gcc -Wall -O0 -g -c -o obj/main.o src/main.c
obj/IntVector.o: src/IntVector.c
	gcc -Wall -O0 -g -c -o obj/IntVector.o src/IntVector.c
