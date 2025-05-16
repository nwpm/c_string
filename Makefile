PROJECT_NAME = c_string
SRC_DIR = src
INTERNAL_DIR = src/internal
INCLUDE_DIR = include

DEBUG_BIN = bin/debug
DEBUG_OBJS = $(DEBUG_BIN)/obj
STR_DEBUG_OBJ = $(DEBUG_OBJS)/c_string.o
INTERNAL_DEBUG_OBJ = $(DEBUG_OBJS)/_str_internal.o
ALL_DEBUG_OBJS = $(STR_DEBUG_OBJ) $(INTERNAL_DEBUG_OBJ)

UNITY_LIB = tests/libs/unity
UNITY_LIB_SRC = $(UNITY_LIB)/src
UNITY_BIN = $(UNITY_LIB)/bin

TESTS_DIR = tests
TESTS_SRC = $(TESTS_DIR)/tests.c
DEBUG_TESTS_BIN = $(DEBUG_BIN)/d_libcstring_tests
DEBUG_TESTS_OBJ = $(DEBUG_OBJS)/d_libcstring_tests.o

# compiler settings
CC = gcc
STANDART = -std=c99
WARNINGS_LEVEL = -Wall -Wextra -Wpedantic
DONT_OPTIMIZE = -O0
MAX_OPTIMIZE = -O3
DEBUG_CFLAGS_ALL = -g $(DONT_OPTIMIZE) $(WARNINGS_LEVEL) $(STANDART) -I$(INCLUDE_DIR) -I$(INTERNAL_DIR) -I$(UNITY_LIB_SRC)
DEBUG_CFLAGS_CSTIRNG = -g $(DONT_OPTIMIZE) $(WARNINGS_LEVEL) $(STANDART) -I$(INCLUDE_DIR) -I$(INTERNAL_DIR)
DEBUG_CFLAGS_TESTS = -fsanitize=address -g $(DONT_OPTIMIZE) $(WARNINGS_LEVEL) $(STANDART) -I$(INCLUDE_DIR) -I$(INTERNAL_DIR) -I$(UNITY_LIB_SRC)


RELEASE_CFLAGS = $(MAX_OPTIMIZE) $(WARNINGS_LEVEL) $(STANDART)

all : $(UNITY_BIN)/libunity.a $(DEBUG_BIN)/d_c_string.a $(DEBUG_TESTS_BIN)

d_tests : $(DEBUG_TESTS_BIN)

$(DEBUG_TESTS_BIN) : $(DEBUG_TESTS_OBJ) $(DEBUG_BIN)/d_c_string.a $(DEBUG_BIN)/libunity.a
	$(CC) $(DEBUG_CFLAGS_TESTS) $^ -o $@

$(DEBUG_TESTS_OBJ) : $(TESTS_SRC) | $(DEBUG_OBJS)
	$(CC) $(DEBUG_CFLAGS_TESTS) -c $< -o $@

d_lib : $(DEBUG_BIN)/d_c_string.a

$(DEBUG_BIN)/d_c_string.a : $(ALL_DEBUG_OBJS)
	ar rcs $@ $^

$(STR_DEBUG_OBJ) : $(SRC_DIR)/c_string.c | $(DEBUG_OBJS)
	$(CC) $(DEBUG_CFLAGS_CSTIRNG) -c $< -o $@

$(INTERNAL_DEBUG_OBJ) : $(INTERNAL_DIR)/_str_internal.c | $(DEBUG_OBJS)
	$(CC) $(DEBUG_CFLAGS_CSTIRNG) -c $< -o $@ 

$(DEBUG_OBJS) :
	mkdir -p $@

unity_lib : $(UNITY_BIN)/libunity.a

$(UNITY_BIN)/libunity.a : $(UNITY_BIN)
	cd $(UNITY_BIN) && cmake ..
	cd $(UNITY_BIN) && make
	mv $(UNITY_BIN)/libunity.a $(DEBUG_BIN)/libunity.a

$(UNITY_BIN) :
	mkdir -p $@

clean :
	rm -rf bin/debug/* $(UNITY_BIN)
