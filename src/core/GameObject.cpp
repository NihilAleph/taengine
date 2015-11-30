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
    component->setParent(this);
    m_components.push_back(component);
}

void GameObject::update(float deltaTime)
{

    // Update every component and child that compounds this Game Object
    for (auto &component: m_components) {
        component->update(deltaTime);
    }

    for (auto &child : m_children) {
        child->update(deltaTime);
    }

}
void GameObject::draw(const Shader& shader, const Camera& camera, const RenderingEngine* renderingEngine)
{

    // Draw every component and child that compounds this Game Object
    for (auto &component: m_components) {
        component->draw(shader, camera, renderingEngine);
    }

    for (auto &child : m_children) {
        child->draw(shader, camera, renderingEngine);
    }
}


void GameObject::addToEngine(RenderingEngine* renderingEngine)
{
    // Add components to engine
    for (auto &component: m_components) {
        component->addToEngine(renderingEngine);
    }

    for (auto &child : m_children) {
        child->addToEngine(renderingEngine);
    }
}

}
