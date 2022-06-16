// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <World/world.h>
#include <Utils/utils.h>
#include <SDL2/SDL_image.h>
#include <Utils/easings.h>

void initObstacle(Obstacle* obstacle, SDL_Renderer * renderer, int x, const char* tex, unsigned int screen_w, unsigned int screen_h)
{
    obstacle->down = 0.0f;
    obstacle->wiggle = 0;
    obstacle->screen_w = screen_w;
    obstacle->screen_h = screen_h;
    
    SDL_Texture* texture = IMG_LoadTexture(renderer, tex);

    if(texture == NULL)
        printf("%sObstacle: unable to create texture : %s %s\n", OUT_RED, tex, OUT_DEF);

    int wh = screen_w / 61;
    obstacle->sprite = createSprite(renderer, texture, x, screen_h - screen_w / 14 - wh + 10, wh, wh);
    obstacle->hide_box = newBoxCollider(x + 10, screen_h - screen_w / 14 - wh + 10, wh - 10, wh / 2);
    pm_addCollider(obstacle->hide_box);
}

void renderObstacle(Obstacle* obstacle)
{
    renderRotateSprite(obstacle->sprite);
}

void updateObstacle(Obstacle* obstacle)
{
    obstacle->sprite->coords->x -= 5;
    obstacle->hide_box->x = obstacle->sprite->coords->x;
    int random = rand() % 10;
    if(obstacle->sprite->coords->x <= -obstacle->sprite->coords->w && obs_can_respawn == true && random == 5)
    {
        obstacle->sprite->coords->x = obstacle->screen_w + 5;
        obstacle->sprite->coords->y = obstacle->screen_h - obstacle->screen_w/4 - obstacle->sprite->coords->h + 10;
        obstacle->down = 0.0f;
        obstacle->wiggle = 0;
        obstacle->sprite->angle = 0;
    }
    if(obstacle->sprite->coords->x < (int)(obstacle->screen_w / 25) && obstacle->sprite->coords->y < obstacle->screen_h)
    {
        obstacle->down += 0.1f;
        obstacle->sprite->coords->y += easeInBack(obstacle->down);
        obstacle->sprite->angle--;
    }
    else if(obstacle->sprite->coords->x < (int)(obstacle->screen_w / 10))
    {
        obstacle->sprite->angle = cos(obstacle->wiggle) * 4;
        obstacle->wiggle++;
    }
}

void shutdownObstacle(Obstacle* obstacle)
{
    freeBoxCollider(obstacle->hide_box);
    destroySprite(obstacle->sprite);
}
