// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __OBSTACLES__
#define __OBSTACLES__

#include <Physics/physics.h>
#include <Kernel/sprite.h>

typedef struct
{
    BoxCollider* hide_box;
    Sprite* sprite;
    unsigned int screen_w;
    unsigned int screen_h;
    float down;
    int wiggle;
} Obstacle;

void initObstacle(Obstacle* obstacle, SDL_Renderer* renderer, int x, const char* tex, unsigned int screen_w, unsigned int screen_h);
void renderObstacle(Obstacle* obstacle);
void updateObstacle(Obstacle* obstacle);
void shutdownObstacle(Obstacle* obstacle);

#endif // __OBSTACLES__
