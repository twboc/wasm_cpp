# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wfatal-errors -w

BGFX_HEADERS = -Ibgfx/include -Ibx/include -Ibimg/include

WASMER_HEADERS = -I/home/hubert/.wasmer/include
WASMER_LINKS = ~/.wasmer/lib/libwasmer.so

# Update linker flags to include the shared library that you just built
LINKER_FLAGS = bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so -lSDL2 -lGL -lX11 -ldl -lpthread -lrt

#This is the target that compiles our executable
all : main.cpp
	$(CC) main.cpp -o  main $(COMPILER_FLAGS) $(WASMER_LINKS) $(LINKER_FLAGS) $(BGFX_HEADERS) $(BGFX_HEADERS) $(WASMER_HEADERS) 