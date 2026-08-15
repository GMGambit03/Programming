CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = rpg

.PHONY: all clean Rebuild

all: $(TARGET)

SRC = *.c jsonCFiles/*.c

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
	rm -f $(TARGET)

Rebuild: clean all
