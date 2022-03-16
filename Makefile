BIN_DIR = ./bin
SRC_DIR = ./src
TEST_DIR = ./test

CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c99

build:
	$(CC) $(CFLAGS) $(SRC_DIR)/*.c -o $(BIN_DIR)/rwc.out

clean:
	rm $(BIN_DIR)/*.out $(BIN_DIR)/*.o

test:
	@./bin/rwc.out -w "*main.c" | awk '{print $1 " " $2 " " $3}' | head -n1 > temp_test1
	@wc ./src/main.c | awk '{print $1 " " $2 " "$3}' > temp_test2
	@diff temp_test1 temp_test2
	@rm temp_test1 temp_test2
