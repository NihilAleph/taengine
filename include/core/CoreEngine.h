#ifndef COREENGINE_H
#define COREENGINE_H

#include "IMainGame.h"
#include "RenderingEngine.h"

namespace taengine {

class CoreEngine
{
    public:
        CoreEngine();
        virtual ~CoreEngine();
        // Initialize Game
        void init(float frameRate, IMainGame* game);

        // Method to initialize and finalize the game loop
        virtual void start();
        virtual void stop();

    private:
        // Boolean that keeps the game running
        bool m_isRunning = false;
        // Framerate for the game
        float m_frameRate;

        // Main game
        IMainGame* m_game;

        // Rendering Engine
        RenderingEngine m_renderingEngine;

        // Max number of update steps so that the loop doesn't enter the spiral of death
        const int MAX_UPDATE_STEPS = 6;

        // Where the game loops
        virtual void run();
};

}

#endif // COREENGINE_H
