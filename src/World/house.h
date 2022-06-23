// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __HOUSE__
#define __HOUSE__

#include <Kernel/sprite.h>
#include <Physics/physics.h>
#include <IO/inputs.h>

typedef struct
{
	Sprite* sprite;
	BoxCollider* door_trigger;
} House;

void initHouse(House* house, SDL_Renderer* renderer, int x, int y);
void renderHouse(House* house);
void updateHouse(House* house, Inputs* inputs);
void destroyHouse(House* house);

#endif // __HOUSE__
