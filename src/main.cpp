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
#include "./WindowFrame/WindowFrame.cpp"
#include "./Renderer/Renderer.cpp"

#include "./wasm_test.cpp"

int main(int argc, char *args[])
{
    WASMNode *testNode = new WASMNode("wasm/build/optimized.wasm");
    testNode->Noop();

    WindowFrame* _window_frame = new WindowFrame();

    _window_frame->InitVideo();

    SDL_Window *window = NULL;
    int WIDTH = 640;
    int HEIGHT = 480;

    SDL_DisplayMode CurrentDisplayMode;

    // // Initialize SDL systems
    // if (SDL_Init(SDL_INIT_VIDEO) < 0)
    // {
    //     printf("SDL could not initialize! SDL_Error: %s\n",
    //            SDL_GetError());

    //     return 1;
    // }

    // Get current display mode of all displays.
    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
    {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &CurrentDisplayMode);
        if (should_be_zero != 0)
        {
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

        }
        else
        {
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, CurrentDisplayMode.w, CurrentDisplayMode.h, CurrentDisplayMode.refresh_rate);
        }
    }

    WIDTH = CurrentDisplayMode.w;
    HEIGHT = CurrentDisplayMode.h;

    //Create a window
    window = SDL_CreateWindow(
        "WASM CPP - DEMO",
        CurrentDisplayMode.w / 4,
        CurrentDisplayMode.h / 4,
        CurrentDisplayMode.w / 2,
        CurrentDisplayMode.h / 2,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n",
               SDL_GetError());
    }

    // Collect information about the window from SDL
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi))
    {
        return 1;
    }

    Renderer *_renderer = new Renderer();
    _renderer->SetPlatformData(wmi);
    _renderer->Bootstrap(WIDTH, HEIGHT);

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
            switch (currentEvent.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
            }
        }
        _renderer->Frame();
    }

    _renderer->Shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}