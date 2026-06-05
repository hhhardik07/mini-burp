CC=gcc

CFLAGS=-Wall -Wextra -g -Iinclude #tells gcc where header are 

SRC=src/main.c src/server.c

TARGET=mini-burp


all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
