// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/sprite.h>
#include <Kernel/Memory/memory.h>

extern float day_light;

Sprite* createSprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
    Sprite* sprite = memAlloc(sizeof(Sprite));
    sprite->texture = texture;

    sprite->renderer = renderer;

    sprite->coords = memAlloc(sizeof(SDL_Rect));
    sprite->coords->x = x;
    sprite->coords->y = y;
    sprite->coords->w = w;
    sprite->coords->h = h;

    sprite->angle = 0.0;

    sprite->rotation_point = memAlloc(sizeof(SDL_Point));
    sprite->rotation_point->x = w / 2;
    sprite->rotation_point->y = h / 2;

    sprite->flip_horizontal = false;
    sprite->flip_vertical = false;

    sprite->day_night_cycle = true;

    return sprite;
}

void setCoords(Sprite *sprite, int x, int y, int w, int h)
{
    sprite->coords->x = x;
    sprite->coords->y = y;
    sprite->coords->w = w;
    sprite->coords->h = h;
}

void renderSprite(Sprite* sprite)
{
    if(sprite->day_night_cycle)
        SDL_SetTextureColorMod(sprite->texture, 128 + (day_light < -8.8 ? -88 : day_light * 10), 128 + (day_light < -8.8 ? -88 : day_light * 10), 255);
    else
        SDL_SetTextureColorMod(sprite->texture, 255, 255, 255);
    SDL_RenderCopy(sprite->renderer, sprite->texture, NULL, sprite->coords);
}

void renderRotateSprite(Sprite* sprite)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(sprite->flip_horizontal)
        flip = SDL_FLIP_HORIZONTAL;
    if(sprite->flip_vertical)
        flip = flip == SDL_FLIP_NONE ? SDL_FLIP_VERTICAL : SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;

    if(sprite->day_night_cycle)
        SDL_SetTextureColorMod(sprite->texture, 128 + (day_light < -8.8 ? -88 : day_light * 10), 128 + (day_light < -8.8 ? -88 : day_light * 10), 255);
    else
        SDL_SetTextureColorMod(sprite->texture, 255, 255, 255);
    SDL_RenderCopyEx(sprite->renderer, sprite->texture, NULL, sprite->coords, sprite->angle, sprite->rotation_point, flip);
}

void destroySprite(Sprite* sprite)
{
    SDL_DestroyTexture(sprite->texture);
    memFree(sprite->coords);
    memFree(sprite->rotation_point);
    memFree(sprite);
}
