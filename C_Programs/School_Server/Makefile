CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = serverDatabase

SRC = main.c client.c server.c database.c menus.c packing.c unpacking.c

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lsqlite3

clean: 
	rm -f $(TARGET)