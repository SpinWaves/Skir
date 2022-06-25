// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>
#include <IO/inputs.h>
#include <World/world.h>
#include <Utils/fps.h>
#include <Kernel/text_manager.h>
#include <Physics/physics.h>
#include <GUI/gui.h>

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Inputs inputs;
    FPS_counter fps;
    TextManager text_manager;
    Player player;
    Map map;
    House house;
    WaterPuddle puddle;
    bool run;
} Application;

bool initApplication(Application *app);
void update(Application *app);
void shutdownApplication(Application *app);

#endif // __APPLICATION__
