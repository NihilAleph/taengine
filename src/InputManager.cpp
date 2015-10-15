#include "InputManager.h"

namespace taengine {
InputManager::InputManager() : m_mouseCoords(0.0f, 0.0f)
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

bool InputManager::isKeyUp(unsigned int keyID)
{
    // Search for value of keyID in current state hash map
    auto it = m_keyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_keyMap.end())
        return !it->second;
    else return true;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
    // Search for value of keyID in current state hash map
    auto it = m_keyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_keyMap.end())
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
    auto it = m_previousKeyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_previousKeyMap.end())
        return !it->second;
    else return true;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
    // Search for value of keyID in previous state hash map
    auto it = m_previousKeyMap.find(keyID);
    // Verify if key exists in map
    if (it != m_previousKeyMap.end())
        return it->second;
    else return false;
}
}
