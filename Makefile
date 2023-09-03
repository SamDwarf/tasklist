CC = gcc
EXEC = tl
FLAGS = -Wall -Werror -pedantic
LIBS = -lncurses

all: obj bin bin/$(EXEC)

obj:
	mkdir obj

bin:
	mkdir bin

clean:
	rm obj/*

clear:
	rm -rf obj
	rm -rf bin

bin/$(EXEC): obj/main.o
	$(CC) obj/*.o -o bin/$(EXEC) $(LIBS)

obj/main.o:
	$(CC) src/main.c -c -o obj/main.o $(FLAGS)
