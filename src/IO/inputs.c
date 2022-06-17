// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <IO/inputs.h>
#include <Kernel/Memory/memory.h>

void initInput(Inputs *in)
{
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        in->keyboard[i][0] = false;
        in->keyboard[i][1] = false;
        if(i < 8)
        {
            in->mouse[i][0] = false;
            in->mouse[i][1] = false;
        }
    }

    in->quit = false;
    in->mx = 0;
    in->my = 0;
}

void updateInput(Inputs *in)
{
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        in->keyboard[i][1] = false;
        if(i < 8)
            in->mouse[i][1] = false;
    }

    while(SDL_PollEvent(&in->events))
    {
        if(in->events.window.event == SDL_WINDOWEVENT_CLOSE)
            in->quit = true;
        switch(in->events.type)
        {
            case SDL_KEYDOWN: 
                in->keyboard[in->events.key.keysym.scancode][0] = true;
                in->keyboard[in->events.key.keysym.scancode][1] = false;
            break;
            case SDL_KEYUP: 
                in->keyboard[in->events.key.keysym.scancode][0] = false;
                in->keyboard[in->events.key.keysym.scancode][1] = true;
            break;
            case SDL_MOUSEBUTTONDOWN:
                in->mouse[in->events.button.button][0] = true;
                in->mouse[in->events.button.button][1] = false;
            break;
            case SDL_MOUSEBUTTONUP:
                in->mouse[in->events.button.button][0] = false;
                in->mouse[in->events.button.button][1] = true;
            break;
            
            default: break;
        }
        if(in->events.type == SDL_MOUSEMOTION) // Mouvement de la souris
        {
            in->mx = in->events.motion.x;
            in->my = in->events.motion.y;
        }
    }
}

bool getKey(Inputs *in, const SDL_Scancode key, ButtonAction action)
{
    return in->keyboard[key][action];
}
bool getMouse(Inputs *in, const uint8_t button, ButtonAction action)
{
    return in->mouse[button][action];
}

inline int getMouseX(Inputs* in)
{
    return in->mx;
}
inline int getMouseY(Inputs* in)
{
    return in->my;
}
