#include "core/IMainGame.h"
#include "core/Time.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "core/InputManager.h"

namespace taengine {

//IMainGame::IMainGame()
//{
//    //ctor
//}
//
//IMainGame::~IMainGame()
//{
//    //dtor
//}

void IMainGame::update(float deltaTime)
{
    InputManager::update();

    m_mainCamera.rotateY(- InputManager::getMouseRelativeCoords().x * 0.01f * deltaTime);
    m_mainCamera.pitch(InputManager::getMouseRelativeCoords().y * 0.01f * deltaTime);

    glm::vec3 movement(0.0f);

    if (InputManager::isKeyDown(SDLK_d)) {
        movement += m_mainCamera.getRight();
    }
    if (InputManager::isKeyDown(SDLK_a)) {
        movement += -m_mainCamera.getRight();
    }
    if (InputManager::isKeyDown(SDLK_w)) {
        movement += m_mainCamera.getForward();
    }
    if (InputManager::isKeyDown(SDLK_s)) {
        movement += -m_mainCamera.getForward();
    }

    m_mainCamera.move(movement * 0.005f * deltaTime);

    m_root.update(deltaTime);
}

}
