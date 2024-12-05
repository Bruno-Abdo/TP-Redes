CC = gcc
CFLAGS = -Wall -g
BIN_DIR = bin

all: bin/client bin/server

bin/client: client.c common.c
	$(CC) $(CFLAGS) -o $@ $^

bin/server: server.c common.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf bin
