# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

# Directories

LIB_DIR = lib
BUILD_DIR = build

# Source files and executable name
SOURCES = *.c ./font/*.c  ./robot/*.c $(LIB_DIR)/rs232.c $(LIB_DIR)/serial.c
EXECUTABLE = $(BUILD_DIR)/RobotWriter

# Required runtime files to copy to build directory
RUNTIME_FILES = *.txt


# Default target: build and create the executable
all: $(BUILD_DIR) $(EXECUTABLE) copy_files

# Create the build directory if it does not exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile and link the executable with AddressSanitizer
$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

# Copy runtime files to the build directory
copy_files: $(BUILD_DIR)
	cp $(RUNTIME_FILES) $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run the executable
run: all
	$(EXECUTABLE)