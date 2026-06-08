CC=gcc

CFLAGS=-Wall -Wextra -g -Iinclude

SRC=src/main.c src/server.c src/client.c

TARGET=mini-burp

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
