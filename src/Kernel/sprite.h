// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __SPRITE__
#define __SPRITE__

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect* coords;
    double angle;
    SDL_Point* rotation_point;
    bool flip_horizontal;
    bool flip_vertical;
    bool day_night_cycle;
} Sprite;

Sprite* createSprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);
void setCoords(Sprite *sprite, int x, int y, int w, int h);
void renderSprite(Sprite* sprite);
void renderRotateSprite(Sprite* sprite);
void destroySprite(Sprite* sprite);

#endif // __SPRITE__
