#include "Time.h"

namespace taengine {

Time::Time()
{
    //ctor
}

Time::~Time()
{
    //dtor
}

Uint32 Time::getTime()
{
    return SDL_GetTicks();
}

}
