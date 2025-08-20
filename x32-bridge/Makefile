PROJECT_NAME := x32-bridge
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')
INCLUDE := $(shell find $(INCLUDE_DIR) -type f -name '*.hpp')

CXX = g++
CXX_FLAGS := -std=c++17 -Wall -fPIC -I$(INCLUDE_DIR) -Ideps/SDL/include
LD_FLAGS := -lpthread


LINUX_BUILD_DIR := $(BUILD_DIR)/linux
WINDOWS_BUILD_DIR := $(BUILD_DIR)/windows

LINUX_OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(LINUX_BUILD_DIR)/%.o, $(SRC))
WINDOWS_OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(WINDOWS_BUILD_DIR)/%.o, $(SRC))


.PHONY: all linux windows clean

deps:
	git clone https://github.com/libsdl-org/SDL.git deps/SDL

-include $(wildcard toolchains/*.mk)


clean:
	rm -rf $(BUILD_DIR)
