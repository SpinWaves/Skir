// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
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
    Sprite* jump_sprites[3];
    Sprite* running_sprites[6];
    BoxCollider* hide_box;
    int animation_frame;
    bool stopMove;
} Player;

void initPlayer(Player* player, SDL_Renderer* renderer, int x, int y);
void renderPlayer(Player* player);
void updatePlayer(Player* player, Inputs* inputs, bool isInsideHouse);
void shutdownPlayer(Player* player);

#endif // __PLAYER__
