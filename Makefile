# src/include path
SRC_DIR = src
INTERNAL_DIR = $(SRC_DIR)/internal
INCLUDE_DIR = include
TEST_DIR = tests
DB_BIN_DIR = bin/debug

# compiler
CC = gcc
DCFLAGS = -g -O0 -Wall -Wextra -std=c99 -I$(INCLUDE_DIR)
CFLAGS = -Wall -Wextra -std=c99 

# .o files
DB_LIB_OBJS = $(DB_BIN_DIR)/c_string.o $(DB_BIN_DIR)/_str_internal.o
TEST_OBJS = $(DB_BIN_DIR)/tests.o
TEST_BIN = $(DB_BIN_DIR)/tests

# target
all : $(DB_BIN_DIR)/db_c_string.a $(TEST_BIN)

# build static lib
$(DB_BIN_DIR)/db_c_string.a : $(DB_LIB_OBJS)
	ar rcs $@ $^

# build source lib
$(DB_BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(DCFLAGS) -c $< -o $@

$(DB_BIN_DIR)/_str_internal.o: $(INTERNAL_DIR)/_str_internal.c | $(DB_BIN_DIR)
	$(CC) $(DCFLAGS) -c $< -o $@

# build tests
$(TEST_BIN): $(TEST_OBJS) $(DB_BIN_DIR)/db_c_string.a
	$(CC) $(CFLAGS) $^ -o $@

$(DB_BIN_DIR)/tests.o: $(TEST_DIR)/tests.c | $(DB_BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DB_BIN_DIR):
	mkdir -p $(DB_BIN_DIR)

# clean
clean:
	rm -rf bin/debug/*

.PHONY: all clean

