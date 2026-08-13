CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = input

.PHONY: all clean Rebuild

SRC = input.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
	rm -f $(TARGET)

Rebuild: clean all
