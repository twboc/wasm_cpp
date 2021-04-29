#ifndef WINDOWFRAME_H
#define WINDOWFRAME_H
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_syswm.h>
	
class WindowFrame  
{
	private:
		SDL_DisplayMode CurrentDisplayMode;

	public:

		WindowFrame();
		~WindowFrame();
		void InitVideo();
		SDL_Window* CreateWindow();
		SDL_DisplayMode SetDisplayMode();

};
#endif