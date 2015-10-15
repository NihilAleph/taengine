#include "Window.h"
#include <GL/glew.h>

namespace taengine {
Window::Window(std::string title, int width, int height, unsigned int currentFlags)
{
    // Initialize window dimensions
    m_width = width;
    m_height = height;
    // Initially the SDL window is dedicated to openGL
    Uint32 flags = SDL_WINDOW_OPENGL;

    // Adding flags to SDL window
    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }
    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }

    // Initialize all SDL functions, just easier
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create the SDL window with constructor params
    SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,height, currentFlags);

    // Create openGL context on SDL window for use with openGL window
    m_glContext = SDL_GL_CreateContext(m_window);
}

Window::~Window()
{
    // Destroy the openGL context
    SDL_GL_DeleteContext(m_glContext);

    // Destroy the SDL window
    SDL_DestroyWindow(m_window);

    // Quit SDL subsystems
    SDL_Quit();
}

void Window::clear(float red, float blue, float green, float alpha)
{
    // Clears the buffer with preset values
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(red, green, blue, alpha);

}
void Window::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}

}
