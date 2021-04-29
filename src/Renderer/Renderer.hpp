#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_syswm.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
	
class Renderer  
{
	private:
		bgfx::PlatformData pd;

	public:

		Renderer();
		~Renderer();
		void SetPlatformData(SDL_SysWMinfo wmi);
		void Bootstrap(int WIDTH, int HEIGHT);
		void Frame();
		void Shutdown();

};
#endif