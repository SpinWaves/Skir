// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/sprite.h>
#include <Kernel/Memory/memory.h>

Sprite* createSprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
    Sprite* sprite = custom_malloc(sizeof(Sprite));
    sprite->texture = texture;
    sprite->renderer = renderer;
    sprite->coords = custom_malloc(sizeof(SDL_Rect));
    sprite->coords->x = x;
    sprite->coords->y = y;
    sprite->coords->w = w;
    sprite->coords->h = h;
    sprite->angle = 0.0;
    sprite->flip_horizontal = false;
    sprite->flip_vertical = false;
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
    SDL_RenderCopy(sprite->renderer, sprite->texture, NULL, sprite->coords);
}

void renderRotateSprite(Sprite* sprite)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(sprite->flip_horizontal)
        flip = SDL_FLIP_HORIZONTAL;
    if(sprite->flip_vertical)
        flip = flip == SDL_FLIP_NONE ? SDL_FLIP_VERTICAL : SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;

    SDL_RenderCopyEx(sprite->renderer, sprite->texture, NULL, sprite->coords, sprite->angle, NULL, flip);
}

void destroySprite(Sprite* sprite)
{
    SDL_DestroyTexture(sprite->texture);
    custom_free(sprite->coords);
    custom_free(sprite);
}
