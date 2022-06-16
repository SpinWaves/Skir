// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __INPUTS__
#define __INPUTS__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    SDL_Event events;
    bool keyboard[SDL_NUM_SCANCODES][2];
    bool mouse[8][2];
    bool quit;
    int mx;
    int my;
} Inputs;

typedef enum { UP = 1, DOWN = 0 } ButtonAction;

void initInput(Inputs *in);
void updateInput(Inputs *in);
bool getKey(Inputs *in, const SDL_Scancode key, ButtonAction action);
bool getMouse(Inputs *in, const uint8_t button, ButtonAction action);
int getMouseX(Inputs* in);
int getMouseY(Inputs* in);

#endif // __INPUTS__
