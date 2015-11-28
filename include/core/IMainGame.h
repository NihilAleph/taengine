#ifndef IMAINGAME_H
#define IMAINGAME_H

#include "core/GameObject.h"
#include "render/Camera.h"
#include "render/Window.h"

namespace taengine {

class IMainGame
{
    public:

        virtual void init() = 0;

        // Methods that are called during the run loop
        void update(float deltaTime);

        GameObject& getRootObject() { return m_root; }
        Camera& getMainCamera() { return m_mainCamera; }
        Window& getWindow() { return m_window; }
    protected:
        GameObject m_root;
        Camera m_mainCamera;
        Window m_window;
};

}
#endif // IMAINGAME_H
