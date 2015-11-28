#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "core/Transform.h"
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
        void draw(Shader& shader, const Camera& camera);
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
