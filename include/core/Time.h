#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>

namespace taengine {

class Time
{
    public:
        Time();
        virtual ~Time();

        // Returns the current time in milliseconds by SDL
        static Uint32 getTime();
    protected:
    private:
};

}

#endif // TIME_H
