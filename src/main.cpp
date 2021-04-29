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
    SDL_DisplayMode CurrentDisplayMode = _window_frame->SetDisplayMode();
    SDL_Window* window = _window_frame->CreateWindow(
        "WASM CPP - DEMO",
        CurrentDisplayMode.w/4,
        CurrentDisplayMode.h/4,
        CurrentDisplayMode.w/2,
        CurrentDisplayMode.h/2,
        SDL_WINDOW_SHOWN
    );

    // Collect information about the window from SDL
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi))
    {
        return 1;
    }

    Renderer *_renderer = new Renderer();
    _renderer->SetPlatformData(wmi);
    _renderer->Bootstrap(CurrentDisplayMode.w, CurrentDisplayMode.h);

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
    _window_frame->Shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}