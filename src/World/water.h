// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __WATER__
#define __WATER__

#include <SDL2/SDL.h>

struct __WaterPoint;
typedef struct __WaterPoint WaterPoint;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	WaterPoint* points;
	SDL_Vertex* vertices;
} WaterPuddle;

void initWaterPuddle(WaterPuddle* puddle, int x, int y, int w, int h);
void updateWaterPuddle(WaterPuddle* puddle);
void renderWaterPuddle(WaterPuddle* puddle, SDL_Renderer* renderer);
void destroyWaterPuddle(WaterPuddle* puddle);

#endif // __WATER__
