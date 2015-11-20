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

        // Input verification
        bool isKeyUp(unsigned int keyID) const;
        bool isKeyDown(unsigned int keyID) const;
        bool isKeyPressed(unsigned int keyID) const;
        bool isKeyReleased(unsigned int keyID) const;

        glm::vec2 getMouseCoords() const { return m_mouseCoords; }
        glm::vec2 getMouseRelativeCoords() const { return m_mouseRelativeCoords; }

    protected:
    private:
        // Hash map of pressed keys
        std::unordered_map<unsigned int, bool> m_keyMap;
        // Hash map of previous pressed keys
        std::unordered_map<unsigned int, bool> m_previousKeyMap;

        // Boolean indicating Quit Event
        bool m_quit = false;

        // Mouse coordinates
        glm::vec2 m_mouseCoords = glm::vec2(0.0f);
        glm::vec2 m_mouseRelativeCoords = glm::vec2(0.0f);


        // Apply input
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);

        // Set mouse coordinates
        void setMouseCoords(float x, float y);
        // Set mouse relative coordinates
        void setMouseRelativeCoords(float x, float y);

        // Previous keys check
        bool wasKeyUp(unsigned int keyID) const;
        bool wasKeyDown(unsigned int keyID) const;
};
}

#endif // INPUTMANAGER_H
