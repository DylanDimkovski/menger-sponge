#include "Chrono.h"

void Chrono::calculate_delta()
{
    endtime = SDL_GetTicks() / 1000.0f;
    elapsed = endtime - starttime;
    if (frames == 100)
    {
        float delta = endtime - last;
        fps = 100.0f / delta;
        frames = 0;
        last = endtime;
    }
    starttime = endtime;
    frames++;
}
