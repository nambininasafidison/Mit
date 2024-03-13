CC=gcc
CFLAGS=-Wall
BIN=main

all: $(BIN)


main: main.c gauss.c
	$(CC) -o $@ $^

run:
	./main

clean:
	rm $(BIN)