#include "core/CoreEngine.h"
#include "core/Time.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <core/InputManager.h>

namespace taengine {

CoreEngine::CoreEngine()
{

}

CoreEngine::~CoreEngine()
{
    //dtor
}

void CoreEngine::init(float frameRate, IMainGame* game)
{
    m_frameRate = frameRate;
    m_game = game;
}

void CoreEngine::start()
{
    if (m_isRunning)
        return;

    m_game->init();
    m_isRunning = true;
    run();
}

void CoreEngine::stop()
{
    if (!m_isRunning)
        return;

    m_isRunning = false;
}

void CoreEngine::run()
{

    // Counter of frames
    int frameCounter = 0;
    // Time counter for frame counting
    Uint32 frameTimeCounter = 0;

    // Initiating time counting
    Uint32 lastTime = Time::getTime();

    // This is the game loop that will keep going until the game stop
    while (m_isRunning) {
        // Calculate the delta time between frames
        Uint32 newTime = Time::getTime();
        float totalDeltaTime = newTime - lastTime;
        lastTime = newTime;

        // Add delta time to frame time counter
        frameTimeCounter += totalDeltaTime;

        // The game will update for each frame cap before rendering
        // So it doesn't lose the physics continuity
        int i = 0;
        while (totalDeltaTime > 0.0f && i < MAX_UPDATE_STEPS) {
            // The delta time for this iteration will be the minimum between the frame cap
            // Or the total delta time remaining.
            float deltaTime = std::min(totalDeltaTime, 1000.0f/m_frameRate);

            // Update the game with deltaTime
            m_game->update(deltaTime);

            // Decrement this iteration processing time from the total delta time
            totalDeltaTime -= deltaTime;
        }

        // Draw the game frame
        m_renderingEngine.draw(m_game->getRootObject(), m_game->getMainCamera(), m_game->getWindow());

        // Iterate frame counter
        frameCounter++;
        // For each second, print frame count (FPS), and reset counters
        if (frameTimeCounter > 1000.0f) {
            std::cout << "FPS: " << frameCounter << std::endl;
            frameCounter = 0;
            frameTimeCounter = 0;
        }

        // If Input Manager detect closure then stop game
        if (InputManager::hasQuitted()) {
            stop();
        }

        if (InputManager::isKeyPressed(SDLK_ESCAPE)) {
            stop();
        }

    }
}

}
