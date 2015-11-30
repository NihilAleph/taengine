#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "core/Transform.h"
#include "render/Shader.h"
#include "render/Camera.h"

namespace taengine {

class GameObject;

class GameComponent
{
    public:
//        GameComponent() {};
//        virtual ~GameComponent() {};

        virtual void update(float deltaTime) {};
        virtual void draw(const Shader& shader, const Camera& camera, const RenderingEngine* renderingEngine) {};

        void setParent(GameObject* parent) { m_parent = parent; }

        virtual void addToEngine(RenderingEngine* renderingEngine) {};
    protected:
        GameObject* m_parent = nullptr;
    private:
};

}

#endif // GAMECOMPONENT_H
