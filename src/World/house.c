// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "house.h"
#include "player.h"
#include <Kernel/kernel.h>
#include <SDL2/SDL_image.h>

#define SCALE 4.5

void initHouse(House* house, SDL_Renderer* renderer, int x, int y)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/world/house.png");

	if(texture == NULL)
		log_report(FATAL_ERROR, "House : unable to create texture : "MAIN_DIR"ressources/Assets/world/house.png");

	int w = 0;
	int h = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	house->sprite = createSprite(renderer, texture, x, y, w * SCALE, h * SCALE);

	house->door_trigger = newBoxCollider(0, 0, 17 * SCALE, 28 * SCALE, false);
}

void renderHouse(House* house)
{
	renderSprite(house->sprite);
}

static int fading = 255;

void updateHouse(House* house, Inputs* inputs)
{
	house->sprite->coords->x = mov_x + 1000;
	house->sprite->coords->y = mov_y + 425;

	house->door_trigger->x = mov_x + 1000 + 93 * SCALE;
	house->door_trigger->y = mov_y + 425 + 135 * SCALE;

	pm_checkCollisionsColliderWithID(house->door_trigger, 0); // check collisions between the door and the player

	if(fading < 255 || (getKey(inputs, SDL_SCANCODE_E, DOWN) && (house->door_trigger->left_collision || house->door_trigger->right_collision || house->door_trigger->top_collision || house->door_trigger->bottom_collision)))
	{
		SDL_SetRenderDrawBlendMode(house->sprite->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(house->sprite->renderer, 0, 0, 0, -fading);
		SDL_Rect rect = { 0, 0, width, height };
		SDL_RenderFillRect(house->sprite->renderer, &rect);
		fading = fading < 0 ? 255 : fading - 10;
	}
}

void destroyHouse(House* house)
{
	destroySprite(house->sprite);
	memFree(house);
}
