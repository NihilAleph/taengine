#include "core/InputManager.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace taengine {


// Hash map of pressed keys
std::unordered_map<unsigned int, bool> InputManager::s_keyMap;
// Hash map of previous pressed keys
std::unordered_map<unsigned int, bool> InputManager::s_previousKeyMap;

// Boolean indicating Quit Event
bool InputManager::s_quit = false;

// Mouse coordinates
glm::vec2 InputManager::s_mouseCoords;
glm::vec2 InputManager::s_mouseRelativeCoords;


void InputManager::update()
{
    // Transfer all values from current input state hash map to the previous one
    for (auto& it : s_keyMap) {
        s_previousKeyMap[it.first] = it.second;
    }
    setMouseRelativeCoords(0.0f,0.0f);

    // Check for inputs
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            s_quit = true;
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
    s_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
    // Value of has is set false
    s_keyMap[keyID] = false;
}

bool InputManager::isKeyUp(unsigned int keyID)
{
    // Search for value of keyID in current state hash map
    auto it = s_keyMap.find(keyID);
    // Verify if key exists in map
    if (it != s_keyMap.end())
        return !it->second;
    else return true;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
    // Search for value of keyID in current state hash map
    auto it = s_keyMap.find(keyID);
    // Verify if key exists in map
    if (it != s_keyMap.end())
        return it->second;
    else return false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
    return wasKeyUp(keyID) && isKeyDown(keyID);
}

bool InputManager::isKeyReleased(unsigned int keyID)
{
    return isKeyUp(keyID) && wasKeyDown(keyID);
}

bool InputManager::wasKeyUp(unsigned int keyID)
{
    // Search for value of keyID in previous state hash map
    auto it = s_previousKeyMap.find(keyID);
    // Verify if key exists in map
    if (it != s_previousKeyMap.end())
        return !it->second;
    else return true;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
    // Search for value of keyID in previous state hash map
    auto it = s_previousKeyMap.find(keyID);
    // Verify if key exists in map
    if (it != s_previousKeyMap.end())
        return it->second;
    else return false;
}

void InputManager::setMouseCoords(float x, float y)
{
    s_mouseCoords.x = x;
    s_mouseCoords.y = y;
}

void InputManager::setMouseRelativeCoords(float xrel, float yrel)
{
    s_mouseRelativeCoords.x = xrel;
    s_mouseRelativeCoords.y = yrel;
}

}
