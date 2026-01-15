CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Werror
TARGET = zcalc

ARGS ?= ""

BUILD ?= "debug"

RAW_LIBS = m
LIBS = $(patsubst %,-l%, $(RAW_LIBS))

# Define source directory
SRC_DIR = src
BLD_DIR = build
INC_DIRS_RAW = include

INC_DIRS = $(patsubst %,-I%, $(INC_DIRS_RAW))
CFLAGS += $(INC_DIRS)
# CFLAGS += -fsanitize=address -fno-omit-frame-pointer
ifeq ($(BUILD),release)
	CFLAGS += "-O3"
else
	CFLAGS += "-O0 -g -fsanitize=address -fno-omit-frame-pointer"
endif

SRCS = $(shell find src -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o, $(SRCS))

# Compile all right now
all: $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS) $^ -o $(TARGET)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	@echo "Compiling file: $< -> $@"
	@if [ ! -d $(@D) ]; then \
		echo "Creating directory: $(@D)"; \
		mkdir -p $(@D); \
	fi
	@$(CC) $(CFLAGS) $< -c -g -o $@

$(BLD_DIR):
	@echo "Creating '$@' directory"
	@mkdir $(BLD_DIR)

run:
	@echo "Running $(TARGET)"
	@./$(TARGET) $(ARGS)

clean:
	@rm -rf $(BLD_DIR)
