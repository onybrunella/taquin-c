# Name of the executable
TARGET = taquin

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# List of source files
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/plateau.c \
      $(SRC_DIR)/graphique.c

# List of object files (derived from sources)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Compiler
CC = gcc
CFLAGS = -Wall -ansi -I$(INCLUDE_DIR) `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs MLV`

# Default rule
all: $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to create the executable
$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Clean up build files and executable
clean:
	rm -rf $(BUILD_DIR) $(TARGET)