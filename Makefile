#TODO: Redo the makefile according to the new structure
# Should be able to do a make run, make build, make test, make clean (more options could be added) 
# make build should compile to obj the files in src and put them in build. Then it should link them (those from source) together and put the executable in bin.
# make test should compile to obj the files in test and put them in build. Then it should link them (those from test) together and put the executable in bin.
# make run should run either the main in bin or the test in bin
# make clean should remove all files in build and bin

BIN_NAME = main

CXX = gcc
LD  = gcc

CXXFLAGS = -Wall -Wextra -pedantic -std=c11 -ggdb

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
BIN = $(BIN_NAME)

vpath %.c $(SRC_DIR)

################################################################################
# Rules
################################################################################

.DEFAULT_GOAL = all

$(BUILD_DIR)/%.o: %.c
	$(CXX) -c $(CXXFLAGS) $< -o $@ -lm

$(BIN_DIR)/$(BIN_NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) -lm

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(BIN_NAME)

clean:
	rm -f $(BUILD_DIR)/* $(BIN_DIR)/* 
