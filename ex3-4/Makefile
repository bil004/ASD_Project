# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
TEST_DIR = test
UNITY_DIR = lib/Unity/src
OBJ_DIR = obj

# Targets
EXEC_MAIN = $(BIN_DIR)/main_ex3-4
EXEC_TEST = $(BIN_DIR)/test_ex3-4

# Source files
SRCS_MAIN = $(SRC_DIR)/main_ex3-4.c $(SRC_DIR)/hashTable.c $(SRC_DIR)/bfs.c $(SRC_DIR)/graph.c
SRCS_TEST = $(SRC_DIR)/test_ex3-4.c $(SRC_DIR)/hashTable.c $(SRC_DIR)/bfs.c $(SRC_DIR)/graph.c $(UNITY_DIR)/unity.c

# Object files
OBJS_MAIN = $(SRCS_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_TEST = $(SRCS_TEST:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(EXEC_MAIN) $(EXEC_TEST)

# Variabili per comandi ripetuti
MKDIR_CMD = @if not exist "$(1)" mkdir "$(1)"
DEL_CMD = @if exist "$(1)" del /Q "$(1)"
RMDIR_CMD = @if exist "$(1)" rmdir /S /Q "$(1)"

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR):
	$(call MKDIR_CMD,$(BIN_DIR))
	$(call MKDIR_CMD,$(OBJ_DIR))

# Main executable
$(EXEC_MAIN): $(OBJS_MAIN) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS_MAIN)

# Test executable
$(EXEC_TEST): $(OBJS_TEST) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS_TEST)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(UNITY_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNITY_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(UNITY_DIR) -c $< -o $@

# Run tests
run_test: $(EXEC_TEST)
	./$(EXEC_TEST)

# Clean build files
clean:
	$(call DEL_CMD,$(OBJ_DIR)\*.o)
	$(call DEL_CMD,$(EXEC_MAIN))
	$(call DEL_CMD,$(EXEC_TEST))
	$(call RMDIR_CMD,$(OBJ_DIR))

cleanAll: clean
	$(call DEL_CMD,$(SRC_DIR)\*~)
	$(call DEL_CMD,$(INC_DIR)\*~)
	$(call DEL_CMD,$(TEST_DIR)\*.exe)
	$(call RMDIR_CMD,$(BIN_DIR))