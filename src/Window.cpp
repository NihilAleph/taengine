#include "Window.h"
#include <GL/glew.h>
#include <iostream>

namespace taengine {

Window::Window()
{

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

void Window::init(std::string title, int width, int height, unsigned int currentFlags)
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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not be initialized!" << std::endl << SDL_GetError() << std::endl;
    }

    // Set buffers sizes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    // Create the SDL window with constructor params
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

    // Check if window was created
    if (m_window == nullptr) {
        std::cerr << "SDL Window could not be opened!" << std::endl << SDL_GetError() << std::endl;
    }

    // Create openGL context on SDL window for use with openGL window
    m_glContext = SDL_GL_CreateContext(m_window);

    // Check if SDL GL context was created
    if (m_glContext == NULL) {
        std::cerr << "SDL_GL context could not be created!" << std::endl << SDL_GetError() << std::endl;
    }

    // Initialize glew
    GLenum res = glewInit();

    // Check if glew was initialized
    if (res != GLEW_OK) {
        std::cerr << "Could not initialize glew!";
    }

    // Checking openGL version
    std::cout << "*** OpenGL Version: " << glGetString(GL_VERSION) << " ***" << std::endl;

    // Enable depth comparison for rendering
	glEnable(GL_DEPTH_TEST);
	// Specifying that should pass if value is less then stored
	glDepthFunc(GL_LESS);

    // Enable Back-face culling, i.e. polygons facing back are not rendered
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Set front face being counterclockwise
	glFrontFace(GL_CCW);


//   // VSYNC is on (1) or off (0)
//   SDL_GL_SetSwapInterval(0);
//
//   // enable alpha blending
//   glEnable(GL_BLEND);
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::clear(float red, float blue, float green, float alpha)
{
    // Clears the buffer with preset values
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Specify clear values for color buffer
    glClearColor(red, green, blue, alpha);

}
void Window::swapBuffers()
{
    // Swap window buffer
    SDL_GL_SwapWindow(m_window);
}

}
