#include "InputManager.h"
#include <SDL2/SDL.h>

namespace taengine {
InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}

void InputManager::update()
{
    // Transfer all values from current input state hash map to the previous one
    for (auto& it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }

    // Check for inputs
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
            pressKey(e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            releaseKey(e.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            pressKey(e.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            releaseKey(e.button.button);
            break;
        case SDL_MOUSEMOTION:
            setMouseCoords(e.motion.x, e.motion.y);
            setMouseRelativeCoords(e.motion.xrel, e.motion.yrel);
            break;
        default:
            break;
        }
    }
}

void InputManager::pressKey(unsigned int keyID)
{
    // Value of hash is set true
    m_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
    // Value of has is set false
    m_keyMap[keyID] = false;
}

bool InputManager::isKeyUp(unsigned int keyID) const
{
    // Search for value of keyID in current state hash map
    auto it = m_keyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_keyMap.end())
        return !it->second;
    else return true;
}

bool InputManager::isKeyDown(unsigned int keyID) const
{
    // Search for value of keyID in current state hash map
    auto it = m_keyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_keyMap.end())
        return it->second;
    else return false;
}

bool InputManager::isKeyPressed(unsigned int keyID) const
{
    return wasKeyUp(keyID) && isKeyDown(keyID);
}

bool InputManager::isKeyReleased(unsigned int keyID) const
{
    return isKeyUp(keyID) && wasKeyDown(keyID);
}

bool InputManager::wasKeyUp(unsigned int keyID) const
{
    // Search for value of keyID in previous state hash map
    auto it = m_previousKeyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_previousKeyMap.end())
        return !it->second;
    else return true;
}

bool InputManager::wasKeyDown(unsigned int keyID) const
{
    // Search for value of keyID in previous state hash map
    auto it = m_previousKeyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_previousKeyMap.end())
        return it->second;
    else return false;
}

void InputManager::setMouseCoords(float x, float y)
{
    m_mouseCoords.x = x;
    m_mouseCoords.y = y;
}

void InputManager::setMouseRelativeCoords(float xrel, float yrel)
{
    m_mouseRelativeCoords.x = xrel;
    m_mouseRelativeCoords.y = yrel;
}

}
