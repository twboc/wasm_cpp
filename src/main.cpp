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

#include "./wasm_test.cpp"


SDL_Window *window = NULL;
int WIDTH = 640;
int HEIGHT = 480;

struct position_t {
    int x;
    int y;
} WindowPosition;


int main(int argc, char *args[])
{
    WASMNode *testNode = new WASMNode("wasm/build/optimized.wasm");

    testNode->Noop();

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