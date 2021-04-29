#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <string>

#include "wasmer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_syswm.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "./WASMNode/WASMNode.cpp"


SDL_Window *window = NULL;
int WIDTH = 640;
int HEIGHT = 480;

struct position_t {
    int x;
    int y;
} WindowPosition;

wasmer_instance_t* GetWasmFile(const char* path, char* _mode = "r") {
    // Read the Wasm file bytes.
    FILE *file = std::fopen(path, "r");
    std::fseek(file, 0, SEEK_END);
    long len = std::ftell(file);
    uint8_t *bytes = static_cast<uint8_t *>(std::malloc(len));
    std::fseek(file, 0, SEEK_SET);
    std::fread(bytes, 1, len, file);
    std::fclose(file);

    // Prepare the imports.
    wasmer_import_t imports[] = {};
 
    // Instantiate!
    wasmer_instance_t *instance = NULL;
    wasmer_result_t instantiation_result = wasmer_instantiate(&instance, bytes, len, imports, 0);
 
    assert(instantiation_result == WASMER_OK);

    return instance;
}

int main(int argc, char *args[])
{


    WASMNode *testNode = new WASMNode();

    testNode->Echo();

    wasmer_instance_t *instance = GetWasmFile("wasm/build/optimized.wasm");
 
    // Let's call a function.
    // Start by preparing the arguments.
 
    // Value of argument #1 is `7i32`.
    wasmer_value_t argument_one;
    argument_one.tag = WASM_I32;
    argument_one.value.I32 = 7;
 
    // Value of argument #2 is `8i32`.
    wasmer_value_t argument_two;
    argument_two.tag = WASM_I32;
    argument_two.value.I32 = 8;
 
    // Prepare the arguments.
    wasmer_value_t arguments[] = {argument_one, argument_two};
 
    // Prepare the return value.
    wasmer_value_t result_one;
    wasmer_value_t results[] = {result_one};
 
    // Call the `sum` function with the prepared arguments and the return value.
    wasmer_result_t call_result = wasmer_instance_call(instance, "add", arguments, 2, results, 1);
 
    // Let's display the result.
    printf("Call result:  %d\n", call_result);
    printf("Result: %d\n", results[0].value.I32);
 
    // // `sum(7, 8) == 15`.
    // assert(results[0].value.I32 == 15);
    // assert(call_result == WASMER_OK);
 
    // wasmer_instance_destroy(instance);

    WindowPosition.x = 0;
    WindowPosition.y = 0;

    SDL_DisplayMode CurrentDisplayMode;

    // Initialize SDL systems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
    else
    {

        // Get current display mode of all displays.
        for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){

            int should_be_zero = SDL_GetCurrentDisplayMode(i, &CurrentDisplayMode);

            if(should_be_zero != 0)
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

            else
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, CurrentDisplayMode.w, CurrentDisplayMode.h, CurrentDisplayMode.refresh_rate);

        }

        WIDTH = CurrentDisplayMode.w;
        HEIGHT = CurrentDisplayMode.h;

        //Create a window
        window = SDL_CreateWindow("WASM CPP - DEMO",
                                  CurrentDisplayMode.w/4,
                                  CurrentDisplayMode.h/4,
                                  CurrentDisplayMode.w/2, CurrentDisplayMode.h/2,
                                  SDL_WINDOW_SHOWN
                                  );

        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }
    }

    // Collect information about the window from SDL
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return 1;
    }
    
    bgfx::PlatformData pd;
    // and give the pointer to the window to pd
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;

    // Tell bgfx about the platform and window
    bgfx::setPlatformData(pd);

    // Render an empty frame
    bgfx::renderFrame();

    // Initialize bgfx
    bgfx::init();
    
    // Reset window
    bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);

    // Enable debug text.
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    // Set view rectangle for 0th view
    bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT));

    // Clear the view rect
    bgfx::setViewClear(0,
                        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                        0x443355FF, 1.0f, 0);

    // Set empty primitive on screen
    bgfx::touch(0);


    // Poll for events and wait till user closes window
    bool quit = false;
    SDL_Event currentEvent;
    while (!quit)
    {
        while (SDL_PollEvent(&currentEvent) != 0)
        {
            if (currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        bgfx::frame();

    }

    // Free up window
    SDL_DestroyWindow(window);
    //close bgfx
    bgfx::shutdown();
    // Shutdown SDL
    SDL_Quit();
    
    return 0;
}