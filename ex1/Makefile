# Detect OS and set specific commands
ifeq ($(OS), Windows_NT)
    RM = rmdir /s /q
    MKDIR = mkdir
    EXE = .exe

else
    RM = rm -rf
    MKDIR = mkdir -p
    EXE =

endif

CC = gcc
UNITY_DIR = ../Resources/C/Unity
CFLAGS = -I$(UNITY_DIR) -Wall -Werror -g -fopenmp

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

TARGET = $(BIN_DIR)/main_ex1$(EXE)
TEST_TARGET = $(BIN_DIR)/test_ex1$(EXE)

.PHONY: all clean test compile build help

# Default target
all: $(TARGET) $(TEST_TARGET)
	@echo "All targets have been built ($(TARGET), $(TEST_TARGET))."

# Create build directory if it does not exist
$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

# Create object directory if it does not exist
$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# Rule for compiling object files
compile: $(OBJ_FILES) $(TEST_OBJ_FILES)
	@echo "Object files have been compiled."

# Rule for creating executables
build: $(TARGET) $(TEST_TARGET)
	@echo "Executables have been built."

# Rule for compiling object files from the source directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for compiling object files from the test directory
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile and link the main application
$(TARGET): $(OBJ_FILES) $(OBJ_DIR)/main.o | $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(OBJ_DIR)/main.o

# Compile and link the test executable
$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES) $(UNITY_SRC) | $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ_FILES) $(OBJ_FILES) $(UNITY_SRC)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up build artifacts
clean:
	$(RM) $(OBJ_DIR) $(BIN_DIR)
	@echo "Build artifacts have been removed (/obj, /bin)."

help:
	@echo "Usage: make [all|clean|test|compile|build|help]"
	@echo "  all: Compile the main application and test executable"
	@echo "  clean: Remove build artifacts"
	@echo "  test: Run tests"
	@echo "  compile: Compile only the object files"
	@echo "  build: Build the executables"
	@echo "  help: Display this help message"
