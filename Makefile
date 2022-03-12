BIN_DIR = ./bin
SRC_DIR = ./src
TEST_DIR = ./test

CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c99

build:
	$(CC) $(CFLAGS) $(SRC_DIR)/*.c -o $(BIN_DIR)/rwc.out

clean:
	rm $(BIN_DIR)/*.out $(BIN_DIR)/*.o
