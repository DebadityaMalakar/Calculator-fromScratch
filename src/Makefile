# Compiler and flags
CXX :=	g++
ASM := nasm
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS :=
ASMFLAGS := -f elf64
TARGET := calculator

# Detect OS
ifeq ($(OS),Windows_NT)
    OS := Windows_NT
else
    OS := $(shell uname -s)
endif

# Directories
ROOT_DIR := ..
SRC_DIR := .
CPP_DIR := $(SRC_DIR)/cpp
ASM_DIR := $(SRC_DIR)/asm
ARCH_DIR := $(SRC_DIR)/arch
BUILD_DIR := $(ROOT_DIR)/build

# Detect architecture
ARCH ?= x86_64
ifeq ($(ARCH),i386)
    ASMFLAGS := -f elf
endif

# Source files
CPP_SOURCES := $(wildcard $(CPP_DIR)/*.cpp)
ASM_SOURCES := $(wildcard $(ASM_DIR)/$(ARCH)/*.asm)
ARCH_SOURCES := $(wildcard $(ARCH_DIR)/$(ARCH)/*.asm)
OBJECTS := $(CPP_SOURCES:$(CPP_DIR)/%.cpp=$(BUILD_DIR)/%.o) \
           $(ASM_SOURCES:$(ASM_DIR)/$(ARCH)/%.asm=$(BUILD_DIR)/%.o) \
           $(ARCH_SOURCES:$(ARCH_DIR)/$(ARCH)/%.asm=$(BUILD_DIR)/%.o)

# Platform-specific options
ifeq ($(OS),Windows_NT)
    TARGET := calculator.exe
    LDFLAGS += -luser32 -lgdi32
    # Use Windows commands
    MKDIR := mkdir
    RM := del /Q /F
    RMDIR := rmdir /Q /S
else
    LDFLAGS += -lm
    # Use Unix commands
    MKDIR := mkdir -p
    RM := rm -f
    RMDIR := rm -rf
endif

# Rules
.PHONY: all clean

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@$(MKDIR) $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile C++ sources
$(BUILD_DIR)/%.o: $(CPP_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile ASM sources
$(BUILD_DIR)/%.o: $(ASM_DIR)/$(ARCH)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Compile arch-specific ASM sources
$(BUILD_DIR)/%.o: $(ARCH_DIR)/$(ARCH)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	@$(RM) $(BUILD_DIR)\* $(TARGET)
	@$(RMDIR) $(BUILD_DIR)