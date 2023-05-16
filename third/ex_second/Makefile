all: main

main: obj/main.o obj/command.o obj/coder.o
	gcc -Wall -o main obj/command.o obj/coder.o obj/main.o
obj/main.o: src/main.c
	gcc -Wall -c -o obj/main.o src/main.c
obj/command.o: src/command.c
	gcc -Wall -c -o obj/command.o src/command.c
obj/coder.o: src/coder.c
	gcc -Wall -c -o obj/coder.o src/coder.c
