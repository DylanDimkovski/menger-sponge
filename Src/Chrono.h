#pragma once
#include <sdl/SDL.h>
#include <iostream>
class Chrono 
{
public:
    void calculate_delta();
    
    float last = 0.0f;
    float starttime = 0.0f;
    float endtime = 0.0f;
    float elapsed = 0.0f;
    int frames = 0.0f;
    float fps = 0.0f;
};