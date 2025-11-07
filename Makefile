# ===============================
#   PMSA - Process Monitoring & Scheduling Analyzer
#   Makefile
# ===============================

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -O2

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Target executable name
TARGET = pmsa

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@echo "🔧 Linking object files..."
	$(CC) $(OBJS) -o $(TARGET)
	@echo "✅ Build complete: ./$(TARGET)"

# Compile .c to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "🧩 Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if not present
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Run the program
run: $(TARGET)
	@echo "🚀 Running PMSA..."
	./$(TARGET)

# Clean build files
clean:
	@echo "🧹 Cleaning build directory..."
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "🧼 Clean complete."

# Rebuild (clean + build)
rebuild: clean all

# ===============================
# End of Makefile
# ===============================

