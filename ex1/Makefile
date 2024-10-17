CC = gcc
UNITY_DIR = ../Resources/C/Unity
CFLAGS = -I$(UNITY_DIR) -Wall -Werror -g

SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES := $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))  # Exclude main.o for tests
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES))

UNITY_SRC = $(UNITY_DIR)/unity.c

TARGET = $(BIN_DIR)/main_ex1
TEST_TARGET = $(BIN_DIR)/test_ex1

# Detect OS and set specific commands
ifeq ($(OS), Windows_NT)
    RM = del /Q
    MKDIR = mkdir
    SLASH = \\
else
    RM = rm -f
    MKDIR = mkdir -p
    SLASH = /
endif

.PHONY: all clean test

all: $(TARGET) $(TEST_TARGET)

# Create build directory if it does not exist
$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# Rule for compiling object files from the source directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for compiling object files from the test directory
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile and link the main application
$(TARGET): $(OBJ_FILES) $(OBJ_DIR)/main.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(OBJ_DIR)/main.o

# Compile and link the test executable
$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES) $(UNITY_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ_FILES) $(OBJ_FILES) $(UNITY_SRC)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up build artifacts
clean:
	$(RM) $(TARGET) $(TEST_TARGET) $(OBJ_DIR)$(SLASH)*.o

help:
	@echo "Usage: make [all|clean|test|help]"
	@echo "  all: Compile the main application and test executable"
	@echo "  clean: Remove build artifacts"
	@echo "  test: Run tests"
	@echo "  help: Display this help message"
