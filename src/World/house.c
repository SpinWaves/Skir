// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "house.h"
#include "player.h"
#include <Kernel/log.h>

void initHouse(House* house, SDL_Renderer* renderer, int x, int y)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/world/house.png");
    
    if(texture == NULL)
        log_report(FATAL_ERROR, "House : unable to create texture : "MAIN_DIR"ressources/Assets/world/house.png");
   /*
    int w = 0;
    int h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    */
    house->sprite = createSprite(renderer, texture, x, y, 128, 100);
}

void renderHouse(House* house)
{
	house->sprite->coords->x = mov_x;
	house->sprite->coords->y = mov_y;
	renderSprite(house->sprite);
}

void updateHouse(House* house)
{

}

void destroyHouse(House* house)
{
	destroySprite(house->sprite);
	memFree(house);
}
