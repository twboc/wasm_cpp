#include "./WindowFrame/WindowFrame.cpp"
#include "./Renderer/Renderer.cpp"

void SimpleLoop()
{
    WindowFrame* _window_frame = new WindowFrame();
    _window_frame->InitVideo();
    SDL_DisplayMode _current_display_mode = _window_frame->SetDisplayMode();
    SDL_Window* window = _window_frame->CreateWindow(
        "WASM CPP - DEMO",
        _current_display_mode.w/4,
        _current_display_mode.h/4,
        _current_display_mode.w/2,
        _current_display_mode.h/2,
        SDL_WINDOW_SHOWN
    );
    SDL_SysWMinfo wmi = _window_frame->GetWMInfo(window);

    Renderer *_renderer = new Renderer();
    _renderer->SetPlatformData(wmi);
    _renderer->Bootstrap(_current_display_mode.w, _current_display_mode.h);

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
}