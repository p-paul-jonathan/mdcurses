CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = src/main.c src/ast.c src/parser.c
OUT = mdcurses
TEST = test.md

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

test: $(OUT)
	./$(OUT) $(TEST)

clean:
	rm -f $(OUT)
