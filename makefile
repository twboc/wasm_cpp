

CC = g++

COMPILER_FLAGS = -Wfatal-errors -w

SRC_DIR := ./src
OBJ_DIR := ./obj

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BGFX_HEADERS = -Ideps/bgfx/include -Ideps/bx/include -Ideps/bimg/include

WASMER_HEADERS = -I/home/hubert/.wasmer/include
WASMER_LINKS = ~/.wasmer/lib/libwasmer.so

# Update linker flags to include the shared library that you just built
LINKER_FLAGS = deps/bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so -lSDL2 -lGL -lX11 -ldl -lpthread -lrt

#This is the target that compiles our executable
all : $(OBJ)
	$(CC) ./src/main.cpp -o  main $(COMPILER_FLAGS) $(WASMER_LINKS) $(LINKER_FLAGS) $(BGFX_HEADERS) $(BGFX_HEADERS) $(WASMER_HEADERS) 