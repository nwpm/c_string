# === Project Info ===
PROJECT_NAME = cstring

# === Paths ===
INCLUDE_DIR  = include
SRC_DIR      = src
INTERNAL_DIR = $(SRC_DIR)/internal
TESTS_SRC    = tests/tests.c

# === Unity (tests) ===
UNITY_LIB     = tests/libs/unity
UNITY_LIB_SRC = $(UNITY_LIB)/src
UNITY_BIN     = $(UNITY_LIB)/bin


# === Compiler ===
CC     = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99

DEBUG_FLAGS   = -g -O0 -fsanitize=address
RELEASE_FLAGS = -O2

INCLUDES      = -I$(INCLUDE_DIR) -I$(INTERNAL_DIR) -I$(UNITY_LIB_SRC)

# === Build type ===
BUILD_TYPE ?= debug

ifeq ($(BUILD_TYPE), debug)
	CFLAGS    += $(DEBUG_FLAGS)
	BUILD_PATH = bin/debug
else ifeq ($(BUILD_TYPE), release)
	CLAGSS    += $(RELEASE_CFLAGS)
	BUILD_PATH = bin/release
else
	$(error Unknown build type: $(BUILD_TYPE))
endif

OBJ_DIR      = $(BUILD_PATH)/obj
LIB_TARGET   = $(BUILD_PATH)/lib$(PROJECT_NAME).a
UNITY_TARGET = $(UNITY_BIN)/libunity.a
TESTS_BIN    = $(BUILD_PATH)/lib$(PROJECT_NAME)_tests

STR_OBJ      = $(OBJ_DIR)/c_string.o
INTERNAL_OBJ = $(OBJ_DIR)/_str_internal.o
TESTS_OBJ    = $(OBJ_DIR)/libcstring_tests.o

# ===Targets===
.PHONY: all test install uninstall clean unity

all: $(TESTS_BIN) $(LIB_TARGET)

test: $(TESTS_BIN)

install: $(LIB_TARGET)
	install -d /usr/local/lib/ /usr/local/include/
	cp $(LIB_TARGET) /usr/local/lib/
	cp $(INCLUDE_DIR)/c_string.h /usr/local/include/

uninstall:
	rm -f /usr/local/lib/lib$(PROJECT_NAME).a
	rm -f /usr/local/include/c_string.h

clean :
	rm -rf $(BUILD_PATH)/* $(UNITY_BIN)

# ===Build rules===
$(TESTS_BIN) : $(TESTS_OBJ) $(LIB_TARGET) $(UNITY_TARGET)
	$(CC) $(CFLAGS) $^ -o $@

$(TESTS_OBJ) : $(TESTS_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIB_TARGET) : $(INTERNAL_OBJ) $(STR_OBJ) | $(BUILD_PATH)
	ar rcs $@ $^

$(STR_OBJ) : $(SRC_DIR)/c_string.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iinclude -I$(INTERNAL_DIR) -c $< -o $@

$(INTERNAL_OBJ) : $(INTERNAL_DIR)/_str_internal.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INTERNAL_DIR) -c $< -o $@ 

$(OBJ_DIR) :
	mkdir -p $@

$(BUILD_PATH):
	mkdir -p $@

# ===Unity rules===

unity: $(UNITY_TARGET)

$(UNITY_TARGET) : $(UNITY_BIN)
	cd $(UNITY_BIN) && cmake ..
	cd $(UNITY_BIN) && make
	cp $(UNITY_BIN)/libunity.a $(BUILD_PATH)/libunity.a

$(UNITY_BIN) :
	mkdir -p $@
