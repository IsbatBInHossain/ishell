CC     = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

ishell: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c include/shell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o ishell

.PHONY: clean