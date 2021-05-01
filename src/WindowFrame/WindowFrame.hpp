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
		SDL_SysWMinfo wmi;

	public:

		WindowFrame();
		~WindowFrame();
		void InitVideo();
		void Shutdown();
		SDL_Window* CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
		SDL_DisplayMode SetDisplayMode();
		SDL_SysWMinfo GetWMInfo(SDL_Window* window);

};
#endif