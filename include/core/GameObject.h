#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "core/Transform.h"
#include "render/Shader.h"
#include "render/RenderingEngine.h"
#include "core/GameComponent.h"
#include <vector>

namespace taengine {

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        void addChild(GameObject* child);
        void addComponent(GameComponent* component);
        void update(float deltaTime);
        void draw(const Shader& shader, const Camera& camera, const RenderingEngine* renderingEngine);

        void addToEngine(RenderingEngine* renderingEngine);

        Transform& getTransform() { return m_transform; }
    protected:
    private:
        Transform m_transform;
        // Game Object has other Game Objects as children that are called recursively
        std::vector<GameObject*> m_children;
        std::vector<GameComponent*> m_components;

};

}
#endif // GAMEOBJECT_H
