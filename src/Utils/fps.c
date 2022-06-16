// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Utils/fps.h>
#include <SDL2/SDL.h>
#include <time.h>

static long get_nanos()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void initFPS(FPS_counter *counter)
{
    counter->timer = SDL_GetTicks();
    counter->before = get_nanos();
    counter->now = counter->before;
    counter->ns = 1000000000.0 / 60.0;
    counter->fps = 0;
    counter->out_fps = 0;
    counter->ticks = 0;
    counter->out_ticks = 0;
    counter->make_update = true;
}
unsigned long getFPS(FPS_counter *counter)
{
    return counter->out_fps;
}
unsigned long getUPS(FPS_counter *counter)
{
    return counter->out_ticks;
}
void updateFPS(FPS_counter *counter)
{
    counter->now = get_nanos();

    if(SDL_GetTicks() - counter->timer > 1000)
    {
        counter->out_fps = counter->fps;
        counter->out_ticks = counter->ticks;
        counter->ticks = 0;
        counter->fps = 0;
        counter->timer += 1000;
    }

    counter->fps++;

    if(counter->now - counter->before >= counter->ns)
    {
        counter->ticks++;
        counter->before += counter->ns;
        counter->make_update = true;
    }
    else
        counter->make_update = false;
}
