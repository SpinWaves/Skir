// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <World/floor.h>
#include <Utils/c_output.h>
#include <SDL2/SDL_image.h>
#include <Utils/utils.h>

void initFloor(Floor* floor, SDL_Renderer* renderer, const char* text_path, unsigned int screen_w, unsigned int screen_h)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, text_path);

    if(texture == NULL)
        printf("%sFloor: unable to create texture : %s %s\n", OUT_RED, text_path, OUT_DEF);

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    for(int i = 0; i < ARRAY_SIZE(floor->floors); i++)
    {
        floor->downs[i] = 0.0f;
        floor->wiggles[i] = 0.0f;
        x = (screen_w / (ARRAY_SIZE(floor->floors) - 1)) * i;
        w = screen_w / (ARRAY_SIZE(floor->floors) - 1);
        y = screen_h - w;
        h = screen_h - y + 10;
        floor->floors[i] = createSprite(renderer, texture, x, y, w, h);
        floor->floors[i]->angle = 0;
    }

    floor->screen_w = screen_w;
    floor->screen_h = screen_h;
}

bool obs_can_respawn = false;

void updateFloor(Floor* floor)
{
    obs_can_respawn = false;
    for(int i = 0; i < ARRAY_SIZE(floor->floors); i++)
    {
        floor->floors[i]->coords->x -= 5;
        
        if(floor->floors[i]->coords->x <= -floor->floors[i]->coords->w)
        {
            floor->floors[i]->coords->x = floor->screen_w;
            floor->floors[i]->coords->y = floor->screen_h - floor->floors[i]->coords->w;
            floor->downs[i] = 0.0f;
            floor->wiggles[i] = 0.0f;
            obs_can_respawn = true;
            floor->floors[i]->angle = 0;
        }

        if(floor->floors[i]->coords->x < (int)(floor->screen_w / 25) && floor->floors[i]->coords->y < floor->screen_h) // To make the floor fall down
        {
            floor->downs[i] += 0.1f;
            floor->floors[i]->coords->y += easeInBack(floor->downs[i]);
            floor->floors[i]->angle--;
        }
        else if(floor->floors[i]->coords->x < (int)(floor->screen_w / 5)) // To make the floor wiggle
        {
            floor->floors[i]->angle = cos(floor->wiggles[i]) * 2;
            floor->wiggles[i] += 0.01f;
            floor->wiggles[i] *= 3.2;
        }
    }
}

void renderFloor(Floor* floor)
{
    for(int i = 0; i < ARRAY_SIZE(floor->floors); i++)
        renderRotateSprite(floor->floors[i]);
}

void shutdownFloor(Floor* floor)
{
    for(int i = 0; i < ARRAY_SIZE(floor->floors); i++)
        destroySprite(floor->floors[i]);
}
