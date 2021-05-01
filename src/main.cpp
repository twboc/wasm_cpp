#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <string>

#include "wasmer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_syswm.h>

#include "./WASMNode/WASMNode.cpp"
#include "./SimpleLoop.cpp"

int main(int argc, char *args[])
{
    WASMNode *testNode = new WASMNode("wasm/build/optimized.wasm");
    testNode->Noop();
    testNode->VariadicCall(1,2,3,4,5,6, "test", "another", "wtf");

    SimpleLoop();
    
    return 0;
}