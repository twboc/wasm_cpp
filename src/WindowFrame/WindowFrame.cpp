#include "WindowFrame.hpp"  
	
WindowFrame::WindowFrame()
{
	
}
	
WindowFrame::~WindowFrame()
{
	
}

void WindowFrame::InitVideo()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
}

SDL_Window* WindowFrame::CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
	return SDL_CreateWindow(
        title,
        x,
        y,
        w,
        h,
        flags
    );
}

SDL_DisplayMode WindowFrame::SetDisplayMode()
{
	SDL_DisplayMode CurrentDisplayMode;

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

    return CurrentDisplayMode;
}