# Detect OS and set specific commands
ifeq ($(OS), Windows_NT)
    RM = del /Q
    MKDIR = mkdir
    SLASH = \\
    EXE = .exe

else
    RM = rm -f
    MKDIR = mkdir -p
    SLASH = /
    EXE =

endif

CC = gcc
UNITY_DIR = ..$(SLASH)Resources$(SLASH)C$(SLASH)Unity
CFLAGS = -I$(UNITY_DIR) -Wall -Werror -g

SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)$(SLASH)*.c)
TEST_FILES = $(wildcard $(TEST_DIR)$(SLASH)*.c)

OBJ_FILES = $(patsubst $(SRC_DIR)$(SLASH)%.c, $(OBJ_DIR)$(SLASH)%.o, $(SRC_FILES))
OBJ_FILES := $(filter-out $(OBJ_DIR)$(SLASH)main.o, $(OBJ_FILES))  # Exclude main.o for tests
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)$(SLASH)%.c, $(OBJ_DIR)$(SLASH)%.o, $(TEST_FILES))

UNITY_SRC = $(UNITY_DIR)$(SLASH)unity.c

TARGET = $(BIN_DIR)$(SLASH)main_ex1$(EXE)
TEST_TARGET = $(BIN_DIR)$(SLASH)test_ex1$(EXE)

.PHONY: all clean test

all: $(TARGET) $(TEST_TARGET)

# Create build directory if it does not exist
$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# Rule for compiling object files from the source directory
$(OBJ_DIR)$(SLASH)%.o: $(SRC_DIR)$(SLASH)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for compiling object files from the test directory
$(OBJ_DIR)$(SLASH)%.o: $(TEST_DIR)$(SLASH)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile and link the main application
$(TARGET): $(OBJ_FILES) $(OBJ_DIR)$(SLASH)main.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(OBJ_DIR)$(SLASH)main.o

# Compile and link the test executable
$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES) $(UNITY_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ_FILES) $(OBJ_FILES) $(UNITY_SRC)

# Run tests
test: $(TEST_TARGET)
	.$(SLASH)$(TEST_TARGET)

# Clean up build artifacts
clean:
	$(RM) $(TARGET) $(TEST_TARGET) $(OBJ_DIR)$(SLASH)*.o

help:
	@echo "Usage: make [all|clean|test|help]"
	@echo "  all: Compile the main application and test executable"
	@echo "  clean: Remove build artifacts"
	@echo "  test: Run tests"
	@echo "  help: Display this help message"
