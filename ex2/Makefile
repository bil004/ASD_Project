EXEC_MAIN = bin/main_ex2
EXEC_TEST = bin/test_ex2

SRC_DIR = src
INC_DIR = include
EXEC_DIR = bin
TEST_DIR = test
UNITY_DIR = lib/Unity/src
OBJ_DIR = obj

SRCS_MAIN = $(SRC_DIR)/main_ex2.c $(SRC_DIR)/correctFile.c $(SRC_DIR)/editDistance.c
SRCS_TEST = $(TEST_DIR)/test_ex2.c $(SRC_DIR)/correctFile.c $(SRC_DIR)/editDistance.c $(UNITY_DIR)/unity.c

OBJS_MAIN = $(SRCS_MAIN:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_TEST = $(SRCS_TEST:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -O2 -I$(INC_DIR) -I$(UNITY_DIR)

MKDIR_CMD = @if not exist "$(1)" mkdir "$(1)"
DEL_CMD = @if exist "$(1)" del /Q "$(1)"
RMDIR_CMD = @if exist "$(1)" rmdir /S /Q "$(1)"

all: $(EXEC_MAIN) $(EXEC_TEST)

# Regola per creare la directory bin e obj se non esistono
$(EXEC_DIR) $(OBJ_DIR):
	$(call MKDIR_CMD,$(EXEC_DIR))
	$(call MKDIR_CMD,$(OBJ_DIR))

# Regola per creare l'eseguibile principale
$(EXEC_MAIN): $(OBJS_MAIN) $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS_MAIN)

# Regola per creare l'eseguibile di test
$(EXEC_TEST): $(OBJS_TEST) $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS_TEST)

# Regola generica per compilare i file .c in .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNITY_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

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
	$(call RMDIR_CMD,$(EXEC_DIR))