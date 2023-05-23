all: main

main: obj/main.o obj/strings.o obj/parser.o
	gcc -Wall -o main obj/strings.o obj/main.o obj/parser.o
obj/main.o: src/main.c
	gcc -Wall -c -o obj/main.o src/main.c
obj/strings.o: src/strings.c
	gcc -Wall -c -o obj/strings.o src/strings.c
obj/parser.o: src/parser.c
	gcc -Wall -c -o obj/parser.o src/parser.c
	
.PHONY: run

run: main
	./main
