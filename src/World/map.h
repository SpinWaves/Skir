// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __MAP__
#define __MAP__

#include <SDL2/SDL.h>
#include <Physics/physics.h>

typedef struct
{
	int tile_set[64][64];
    BoxCollider* hide_boxes[64][64];
} Map;

void initMap(Map* map, SDL_Renderer* renderer);
void renderMap(Map* map);
void updateMap(Map* map, bool isInsideHouse);
void destroyMap(Map* map);

#endif // __MAP__
