CC=gcc

CFLAGS=-Wall -Wextra -g

SRC=src/main.c

TARGET=mini-burp


all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
