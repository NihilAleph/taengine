#include "core/GameObject.h"

namespace taengine {

GameObject::GameObject()
{
    //ctor
}

GameObject::~GameObject()
{

}


void GameObject::addChild(GameObject* child)
{
    m_children.push_back(child);
}

void GameObject::addComponent(GameComponent* component)
{
    m_components.push_back(component);
}

void GameObject::update(float deltaTime)
{

    // Update every component and child that compounds this Game Object
    for (auto &component: m_components) {
        component->update(m_transform, deltaTime);
    }

    for (auto &child : m_children) {
        child->update(deltaTime);
    }

}
void GameObject::draw(Shader& shader, const Camera& camera)
{

    // Draw every component and child that compounds this Game Object
    for (auto &component: m_components) {
        component->draw(m_transform, shader, camera);
    }

    for (auto &child : m_children) {
        child->draw(shader, camera);
    }
}

}
