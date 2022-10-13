# Should be able to do a make run, make build, make test, make clean (more options could be added) 
# make build should compile to obj the files in src and put them in build. Then it should link them (those from source) together and put the executable in bin.
# make test should compile to obj the files in test and put them in build. Then it should link them (those from test) together and put the executable in bin.
# make run should run either the main in bin or the test in bin
# make clean should remove all files in build and bin

# Black        0;30     Dark Gray     1;30
# Red          0;31     Light Red     1;31
# Green        0;32     Light Green   1;32
# Brown/Orange 0;33     Yellow        1;33
# Blue         0;34     Light Blue    1;34
# Purple       0;35     Light Purple  1;35
# Cyan         0;36     Light Cyan    1;36
# Light Gray   0;37     White         1;37

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
NC=\033[0m # No Color

# Executables
RUN_BIN=run
TEST_BIN=test

# Compiler & Flags & Libraries
CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11 -ggdb
#LIBS=-lm

# Directories
BIN_DIR=bin
SRC_DIR=src
TEST_DIR=test
BUILD_DIR=build
SOURCES=$(shell find $(SRC_DIR) -name '*.c')

# Variables
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
TEST_FILES=$(wildcard $(TEST_DIR)/*.c)
OBJ_SRC_FILES=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
OBJ_TEST_FILES=$(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_FILES))

# Rules
.PHONY: bin build src test # This is to make sure that the rules are not files
.DEFAULT_GOAL := help

############################################
# Main program rules #######################
############################################
build:
	@echo "$(BLUE)Building & Compiling Program:$(NC)"
	@$(MAKE) --no-print-directory $(BIN_DIR)/$(RUN_BIN)
	@echo "$(GREEN)Successfully built & compiled program!\n$(NC)"

$(BIN_DIR)/$(RUN_BIN): $(OBJ_SRC_FILES)
	$(CC) $(CFLAGS) $(OBJ_SRC_FILES) -o $(BIN_DIR)/$(RUN_BIN)

$(OBJ_SRC_FILES): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

############################################
# Test rules ###############################
############################################
tests:
	@echo "$(BLUE)Building & Compiling Tests:$(NC)"
	@$(MAKE) --no-print-directory $(BIN_DIR)/$(TEST_BIN)
	@echo "$(GREEN)Successfully built & compiled tests!\n$(NC)"

$(BIN_DIR)/$(TEST_BIN): $(OBJ_TEST_FILES)
	$(CC) $(CFLAGS) $(OBJ_TEST_FILES) -o $(BIN_DIR)/$(TEST_BIN)

$(OBJ_TEST_FILES): $(BUILD_DIR)/%.o : $(TEST_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@


############################################
# Run rules ################################
############################################
run: build
	@echo "$(BLUE)Running program:$(NC)"
	@./$(BIN_DIR)/$(RUN_BIN)
	@echo "$(GREEN)Program finished!\n$(NC)"

test: tests
	@echo "$(BLUE)Running Tests:$(NC)"
	@./$(BIN_DIR)/$(TEST_BIN)
	@echo "$(GREEN)Tests finished!\n$(NC)"


############################################
# Clean rules ##############################
############################################
clean: create-dirs
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/*

create-dirs:
	@mkdir -p $(BIN_DIR) $(BUILD_DIR)


############################################	
# Help rules ###############################
############################################
help:
	@echo "$(BLUE)Makefile for the project:$(NC)"
	@echo " "
	@echo "$(CYAN)Usage:"
	@echo "    $(PURPLE)make run       	$(NC)🏃 Runs the program and compiles it if it's not already compiled."
	@echo "    $(PURPLE)make test       	$(NC)🏃 Runs the tests and compiles them if they're not already compiled."
	@echo "    $(PURPLE)make build      	$(NC)⚙️  Builds and compiles the main program."
	@echo "    $(PURPLE)make tests      	$(NC)🎯 Builds and compiles Unit tests."
	@echo "    $(PURPLE)make clean      	$(NC)🧹 Clean up project."