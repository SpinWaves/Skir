// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __PLAYER__
#define __PLAYER__

#include <Kernel/sprite.h>
#include <IO/inputs.h>
#include <Physics/physics.h>

typedef struct
{
    Sprite* idle_sprites[3];
    Sprite* running_sprites[6];
    BoxCollider* hide_box;
    int animation_frame;
    bool stopMove;
} Player;

extern float mov_x;
extern float mov_y;

void initPlayer(Player* player, SDL_Renderer* renderer, int x, int y);
void renderPlayer(Player* player);
void updatePlayer(Player* player, Inputs* inputs);
void shutdownPlayer(Player* player);

#endif // __PLAYER__
