#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL2\SDL.h>

/************************************************
*
*   This class manages the creating, update and destruction of a window.
*   It will be able to configure the settings of the window
*
*************************************************/

namespace taengine {

// Public flags to create the window
enum WindowFlag { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window
{
    public:
        Window(std::string title, int width, int height, unsigned int currentFlags = 0x0);
        virtual ~Window();

        // Clears the window content and fill with color
        void clear(float red, float blue, float green, float alpha);
        // Update window rendering by changing buffers
        void swapBuffers();

        // Window dimensions getters
        inline int getWidth() const { return m_width; }
        inline int getHeight() const { return m_height; }
    protected:
    private:
        // Pointer to SDL window
        SDL_Window* m_window = nullptr;
        // SDL Context
        SDL_GLContext m_glContext;
        // Window dimensions
        int m_width = 0;
        int m_height = 0;

};
}
#endif // WINDOW_H
