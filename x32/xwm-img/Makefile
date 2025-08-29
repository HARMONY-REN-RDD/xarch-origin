PROJECT_NAME := xarch-origin-x32_linux.xwm
BUILD_DIR := build
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := $(BUILD_DIR)/obj

TARGET := $(BUILD_DIR)/$(PROJECT_NAME)

CXX ?= g++
CXX_FLAGS ?= -std=c++20 -Wall -I$(INCLUDE_DIR) -fPIC
LD_FLAGS :=

SRC := $(shell find $(SRC_DIR) -type f -name "*.cpp")
INCLUDE := $(shell find $(INCLUDE_DIR) -type f -name "*.cpp")
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CXX) -shared $(CXX_FLAGS) $(OBJ) -o $@ $(LD_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(INCLUDE) $(OBJ_DIR) 
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

test: all
	xwm -e ./$(TARGET)

.PHONY: all clean test
