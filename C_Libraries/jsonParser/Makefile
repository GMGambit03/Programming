CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = jsonParser

.PHONY: all clean Rebuild

SRC = main.c jsonChecker.c getFile.c structs.c lexer.c parse.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
	rm -f $(TARGET)

Rebuild: clean all
