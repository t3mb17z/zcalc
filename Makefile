CC = clang-19
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Werror
TARGET = zcalc
RAW_LIBS = ncursesw m
LIBS = $(patsubst %,-l%, $(RAW_LIBS))

# Define source directory
SRC_DIR = src
BLD_DIR = build
INC_DIRS_RAW = include

INC_DIRS = $(patsubst %,-I%, $(INC_DIRS_RAW))
CFLAGS += $(INC_DIRS)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o, $(SRCS))

# Compile all right now
all: $(OBJS)
	@$(CC) $(CFLAGS) $^ -g -o $(TARGET)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	@echo "Compiling file: $< -> $@"
	@$(CC) $(CFLAGS) $< -c -g -o $@

$(BLD_DIR):
	@echo "Creating '$@' directory"
	@mkdir $(BLD_DIR)

run:
	@echo "Running $(TARGET)"
	@./$(TARGET)
