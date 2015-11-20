#ifndef IMAINGAME_H
#define IMAINGAME_H

namespace taengine {

class IMainGame
{
    public:
//        IMainGame();
//        virtual ~IMainGame();

        // Method to initialize and finalize the game loop
        virtual void start();
        virtual void stop();

    protected:
        // Boolean that keeps the game running
        bool m_isRunning = false;

        // Constant use to get the frame cap
        const float DESIRED_FPS = 5000.0f;
        // Max number of update steps so that the loop doesn't enter the spiral of death
        const int MAX_UPDATE_STEPS = 6;

        // Where the game loops
        virtual void run();

        // Methods that are called during the run loop
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;

    private:
};

}
#endif // IMAINGAME_H
