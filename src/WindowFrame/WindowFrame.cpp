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