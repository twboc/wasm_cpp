#include "Renderer.hpp"  
	
Renderer::Renderer()
{
	
}
	
Renderer::~Renderer()
{
	bgfx::shutdown();
}

void Renderer::SetPlatformData(SDL_SysWMinfo wmi)
{
    this->pd.ndt = wmi.info.x11.display;
    this->pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
    bgfx::setPlatformData(pd);
}

void Renderer::Bootstrap(int WIDTH, int HEIGHT)
{
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
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

    // Set empty primitive on screen
    bgfx::touch(0);
}

void Renderer::Frame()
{
    bgfx::frame();
}

void Renderer::Loop()
{
    bool quit = false;
    while (!quit)
    {
        this->Frame();
    }
}

void Renderer::Shutdown()
{
    delete this;
}