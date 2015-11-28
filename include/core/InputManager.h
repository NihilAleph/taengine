#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm\glm.hpp>
#include <SDL2/SDL.h>

namespace taengine {
class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        // Update the hash maps per iteration
        static void update();

        // Input verification
        static bool isKeyUp(unsigned int keyID);
        static bool isKeyDown(unsigned int keyID);
        static bool isKeyPressed(unsigned int keyID);
        static bool isKeyReleased(unsigned int keyID);

        static glm::vec2 getMouseCoords() { return s_mouseCoords; };
        static glm::vec2 getMouseRelativeCoords() { return s_mouseRelativeCoords; };

        static bool hasQuitted() { return s_quit; };

    protected:
    private:
        // Hash map of pressed keys
        static std::unordered_map<unsigned int, bool> s_keyMap;
        // Hash map of previous pressed keys
        static std::unordered_map<unsigned int, bool> s_previousKeyMap;

        // Boolean indicating Quit Event
        static bool s_quit;

        // Mouse coordinates
        static glm::vec2 s_mouseCoords;
        static glm::vec2 s_mouseRelativeCoords;


        // Apply input
        static void pressKey(unsigned int keyID);
        static void releaseKey(unsigned int keyID);

        // Set mouse coordinates
        static void setMouseCoords(float x, float y);
        // Set mouse relative coordinates
        static void setMouseRelativeCoords(float x, float y);

        // Previous keys check
        static bool wasKeyUp(unsigned int keyID);
        static bool wasKeyDown(unsigned int keyID);
};
}

#endif // INPUTMANAGER_H
