// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "water.h"
#include <Kernel/kernel.h>
#include <Utils/utils.h>
#include <Maths/maths.h>

extern float mov_x;
extern float mov_y;

#define RATIO 5

struct __WaterPoint
{
	SDL_Point position;
	float velocity;
	float leftDelta;
	float rightDelta;
};

void initWaterPuddle(WaterPuddle* puddle, int x, int y, int w, int h)
{
	if(puddle == NULL)
		log_report(FATAL_ERROR, "Water Puddle : pointer passed is NULL");

	puddle->x = x;
	puddle->y = y;
	puddle->w = w;
	puddle->h = h;

	puddle->points = (WaterPoint*)memAlloc(sizeof(WaterPoint) * (puddle->w / RATIO));
	if(puddle->points == NULL)
		log_report(FATAL_ERROR, "Water Puddle : unable to alloc memory for points");

	puddle->vertices = (SDL_Vertex*)memAlloc(sizeof(SDL_Vertex) * ((puddle->w / RATIO) * 6));
	if(puddle->vertices == NULL)
		log_report(FATAL_ERROR, "Water Puddle : unable to alloc memory for vertices");

	int v = 0;
	for(int i = 0; i < puddle->w / RATIO; i++)
	{
		puddle->points[i].position.x = x + i * RATIO;
		puddle->points[i].position.y = y;
		puddle->points[i].velocity = 0.0f;
		puddle->points[i].leftDelta = 0.0f;
		puddle->points[i].rightDelta = 0.0f;
 
		puddle->vertices[v].position.x = puddle->points[i].position.x;
		puddle->vertices[v].position.y = puddle->points[i].position.y;
		puddle->vertices[v].color.r = 72; puddle->vertices[v].color.g = 165; puddle->vertices[v].color.b = 255; puddle->vertices[v].color.a = 225;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x + RATIO;
		puddle->vertices[v].position.y = puddle->points[i].position.y;
		puddle->vertices[v].color.r = 72; puddle->vertices[v].color.g = 165; puddle->vertices[v].color.b = 255; puddle->vertices[v].color.a = 225;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x + RATIO;
		puddle->vertices[v].position.y = y + h;
		puddle->vertices[v].color.r = 0; puddle->vertices[v].color.g = 100; puddle->vertices[v].color.b = 200; puddle->vertices[v].color.a = 225;
		v++;

		puddle->vertices[v].position.x = puddle->points[i].position.x;
		puddle->vertices[v].position.y = puddle->points[i].position.y;
		puddle->vertices[v].color.r = 72; puddle->vertices[v].color.g = 165; puddle->vertices[v].color.b = 255; puddle->vertices[v].color.a = 225;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x + RATIO;
		puddle->vertices[v].position.y = y + h;
		puddle->vertices[v].color.r = 0; puddle->vertices[v].color.g = 100; puddle->vertices[v].color.b = 200; puddle->vertices[v].color.a = 225;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x;
		puddle->vertices[v].position.y = y + h;
		puddle->vertices[v].color.r = 0; puddle->vertices[v].color.g = 100; puddle->vertices[v].color.b = 200; puddle->vertices[v].color.a = 225;
		v++;
	}
}

extern int width;
extern int height;

static float mov_y_save = 0.0f;

const float springconstant = 0.1f;
const float damping = 0.2f;
const float spread = 0.2f;
const float collisionVelocityFactor = 5.0f;

static double frame = 0.0;

void updateWaterPuddle(WaterPuddle* puddle)
{
	if(frame > 1000.0)
		frame = 0.0;

	for(int i = 0; i < puddle->w / RATIO; i++)
	{
		puddle->points[i].position.x = puddle->x + i * RATIO + mov_x;
		puddle->points[i].position.y = puddle->y + mov_y + puddle->points[i].velocity + 4 * (sin(2 * frame + i * 2));
		frame += 0.00025;

		if(fsqrt(pow(puddle->points[i].position.x + DIV_BY_2(RATIO) - DIV_BY_2(width), 2) + pow(puddle->points[i].position.y + DIV_BY_2(RATIO) - DIV_BY_2(height), 2)) < RATIO * 4)
			puddle->points[i].velocity = (mov_y_save - mov_y) * collisionVelocityFactor;


		puddle->points[i].velocity += -(springconstant * (puddle->points[i].position.y - (puddle->y + mov_y)) + puddle->points[i].velocity * damping);
	}

	for(int i = 0; i < puddle->w / RATIO; i++)
	{
		if(i > 0)
		{
			puddle->points[i].leftDelta = spread * (puddle->points[i].position.y - puddle->points[i - 1].position.y);
			puddle->points[i - 1].velocity += puddle->points[i].leftDelta;
		}
		if(i < puddle->w / RATIO - 1)
		{
			puddle->points[i].rightDelta = spread * (puddle->points[i].position.y - puddle->points[i + 1].position.y);
			puddle->points[i + 1].velocity += puddle->points[i].rightDelta;
		}
	}

	int v = 0;
	for(int i = 0; i < puddle->w / RATIO; i++)
	{
		puddle->vertices[v].position.x = puddle->points[i].position.x;
		puddle->vertices[v].position.y = puddle->points[i].position.y;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x + RATIO;
		puddle->vertices[v].position.y = puddle->points[i].position.y;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x + RATIO;
		puddle->vertices[v].position.y = puddle->y + puddle->h + mov_y;
		v++;

		puddle->vertices[v].position.x = puddle->points[i].position.x;
		puddle->vertices[v].position.y = puddle->points[i].position.y;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x + RATIO;
		puddle->vertices[v].position.y = puddle->y + puddle->h + mov_y;
		v++;
		puddle->vertices[v].position.x = puddle->points[i].position.x;
		puddle->vertices[v].position.y = puddle->y + puddle->h + mov_y;
		v++;
	}

	mov_y_save = mov_y;
}

void renderWaterPuddle(WaterPuddle* puddle, SDL_Renderer* renderer)
{
	SDL_RenderGeometry(renderer, NULL, puddle->vertices, (puddle->w / RATIO) * 6, NULL, 0);
}

void destroyWaterPuddle(WaterPuddle* puddle)
{
	memFree(puddle->points);
	memFree(puddle->vertices);
}
