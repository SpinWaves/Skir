// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "house.h"
#include "player.h"
#include <Kernel/kernel.h>
#include <Utils/utils.h>
#include <Maths/maths.h>
#include <SDL2/SDL_image.h>

void initHouse(House* house, SDL_Renderer* renderer, int x, int y)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/world/house.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "House : unable to create texture : "MAIN_DIR"ressources/Assets/world/house.png");
	int w = 0;
	int h = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	house->sprite = createSprite(renderer, texture, x, y, w * HOUSE_SCALE, h * HOUSE_SCALE);

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/world/house_interior_1.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "House : unable to create texture : "MAIN_DIR"ressources/Assets/world/house_interior_1.png");
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	house->indoor[0] = createSprite(renderer, texture, x, y, w * HOUSE_SCALE, h * HOUSE_SCALE);

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/world/house_interior_2.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "House : unable to create texture : "MAIN_DIR"ressources/Assets/world/house_interior_2.png");
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	house->indoor[1] = createSprite(renderer, texture, x, y, w * HOUSE_SCALE, h * HOUSE_SCALE);

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/world/house_door.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "House : unable to create texture : "MAIN_DIR"ressources/Assets/world/house_door.png");
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_SetTextureAlphaMod(texture, 128);
	house->indoor[2] = createSprite(renderer, texture, x, y, w * HOUSE_SCALE, h * HOUSE_SCALE);

	house->door_trigger = newBoxCollider(0, 0, 17 * HOUSE_SCALE, 28 * HOUSE_SCALE, false);
	house->bed_trigger = newBoxCollider(0, 0, 30 * HOUSE_SCALE, 8 * HOUSE_SCALE, false);

	house->isInside = false;
}

void renderHouse(House* house)
{
	if(!house->isInside)
		renderSprite(house->sprite);
	else
		renderSprite(house->indoor[0]);
}

void renderHouse2(House* house)
{
	if(house->isInside)
	{
		renderSprite(house->indoor[1]);
		renderSprite(house->indoor[2]);
	}
}

extern int fading;
extern ColorRGB clearColor;

void updateHouse(House* house, Inputs* inputs)
{
	if(!house->isInside)
	{
		house->sprite->coords->x = mov_x + 1000;
		house->sprite->coords->y = mov_y + 425;
	}
	else
	{
		house->indoor[0]->coords->x = mov_x + 1000;
		house->indoor[0]->coords->y = mov_y + 435;
		house->indoor[1]->coords->x = mov_x + 1000;
		house->indoor[1]->coords->y = mov_y + 435;
		house->indoor[2]->coords->x = mov_x + 1000;
		house->indoor[2]->coords->y = mov_y + 426;
		house->bed_trigger->x = mov_x + 1000 + 15 * HOUSE_SCALE;
		house->bed_trigger->y = mov_y + 435 + 115 * HOUSE_SCALE;

		pm_checkCollisionsColliderWithID(house->bed_trigger, 0); // check collisions between the bed and the player

		if((fading < 255 || getKey(inputs, SDL_SCANCODE_E, DOWN)) && (house->bed_trigger->left_collision || house->bed_trigger->right_collision || house->bed_trigger->top_collision || house->bed_trigger->bottom_collision))
			fading = fading < -255 ? 255 : fading - 5;
	}

	house->door_trigger->x = mov_x + 1000 + 93 * HOUSE_SCALE;
	house->door_trigger->y = mov_y + 425 + 135 * HOUSE_SCALE;

	pm_checkCollisionsColliderWithID(house->door_trigger, 0); // check collisions between the door and the player

	if((fading < 255 || getKey(inputs, SDL_SCANCODE_E, DOWN)) && (house->door_trigger->left_collision || house->door_trigger->right_collision || house->door_trigger->top_collision || house->door_trigger->bottom_collision))
	{
		if(fading == -5)
		{
			house->isInside = !house->isInside;

			if(house->isInside)
			{
				clearColor.r = 0;
				clearColor.g = 0;
				clearColor.b = 0;
			}
			else
			{
				clearColor.r = 141;
				clearColor.g = 186;
				clearColor.b = 255;
			}
		}

		fading = fading < -255 ? 255 : fading - 10;
	}
}

void destroyHouse(House* house)
{
	destroySprite(house->sprite);
	for(int i = 0; i < ARRAY_SIZE(house->indoor); i++)
		destroySprite(house->indoor[i]);
	memFree(house);
}
