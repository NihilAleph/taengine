#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm\glm.hpp>

namespace taengine {
class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        // Update the hash maps per iteration
        void update();

        // Apply input
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);

        // Input verification
        bool isKeyUp(unsigned int keyID);
        bool isKeyDown(unsigned int keyID);
        bool isKeyPressed(unsigned int keyID);
        bool isKeyReleased(unsigned int keyID);

        // Set mouse coordinates
        void setMouseCoords(float x, float y);
        glm::vec2 getMouseCoords() const { return m_mouseCoords; }

    protected:
    private:
        // Hash map of pressed keys
        std::unordered_map<unsigned int, bool> m_keyMap;
        // Hash map of previous pressed keys
        std::unordered_map<unsigned int, bool> m_previousKeyMap;

        // Mouse coordinates
        glm::vec2 m_mouseCoords;

        // Previous keys check
        bool wasKeyUp(unsigned int keyID);
        bool wasKeyDown(unsigned int keyID);
};
}

#endif // INPUTMANAGER_H
