// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "water.h"
#include <Kernel/kernel.h>
#include <Utils/utils.h>

struct __WaterPoint
{
	SDL_Point position;
	float velocity;
};

void updateWaterPoint(WaterPoint* point, float lastHeight, float newHeight)
{
	//point->position += point->velocity;
	point->velocity += -0.025f * (lastHeight - newHeight);
}

void initWaterPuddle(WaterPuddle* puddle, int x, int y, int w, int h)
{
	if(puddle == NULL)
		log_report(FATAL_ERROR, "Water Puddle : pointer passed is NULL");

	puddle->x = x;
	puddle->y = y;
	puddle->w = w;
	puddle->h = h;

	puddle->points = (WaterPoint*)memAlloc(sizeof(WaterPoint) * (int)(w / 5));
	if(puddle->points == NULL)
		log_report(FATAL_ERROR, "Water Puddle : unable to alloc memory for points");

	printf("%d\n", ARRAY_SIZE(puddle->points));
	puddle->vertices = (SDL_Vertex*)memAlloc(sizeof(SDL_Vertex) * (ARRAY_SIZE(puddle->points) + 2));
	if(puddle->vertices == NULL)
		log_report(FATAL_ERROR, "Water Puddle : unable to alloc memory for vertices");

	for(int i = 0; i < ARRAY_SIZE(puddle->points); i++)
	{
		puddle->points[i].position.x = x + i * ARRAY_SIZE(puddle->points);
		puddle->points[i].position.y = y;
		puddle->points[i].velocity = 0.0f;

		puddle->vertices[i].position.x = puddle->points[i].position.x;
		puddle->vertices[i].position.y = puddle->points[i].position.y;
		puddle->vertices[i].color.r = 94;
		puddle->vertices[i].color.g = 189;
		puddle->vertices[i].color.b = 247;
		puddle->vertices[i].color.a = 128;
	}

	int size = ARRAY_SIZE(puddle->points);

	puddle->vertices[size].position.x = x;
	puddle->vertices[size].position.y = y + h;
	puddle->vertices[size].color.r = 94;
	puddle->vertices[size].color.g = 189;
	puddle->vertices[size].color.b = 247;
	puddle->vertices[size].color.a = 128;

	puddle->vertices[size + 1].position.x = x + w;
	puddle->vertices[size + 1].position.y = y + h;
	puddle->vertices[size + 1].color.r = 94;
	puddle->vertices[size + 1].color.g = 189;
	puddle->vertices[size + 1].color.b = 247;
	puddle->vertices[size + 1].color.a = 128;
}

void updateWaterPuddle(WaterPuddle* puddle)
{
	/*
	for(int i = 0; i < ARRAY_SIZE(puddle->points); i++)
	{
		puddle->points[i].position.x = puddle->x + i * ARRAY_SIZE(puddle->points);
		puddle->points[i].position.y = puddle->y;

		puddle->vertices[i].position.x = puddle->points[i].position.x;
		puddle->vertices[i].position.y = puddle->points[i].position.y;
	}
	*/
}

void renderWaterPuddle(WaterPuddle* puddle, SDL_Renderer* renderer)
{
	printf("%d\n", ARRAY_SIZE(puddle->vertices));
	if(SDL_RenderGeometry(renderer, NULL, puddle->vertices, ARRAY_SIZE(puddle->vertices), NULL, 0) == -1)
		log_report(ERROR, "Water Puddle : unable to be rendered");
}

void destroyWaterPuddle(WaterPuddle* puddle)
{
	memFree(puddle->points);
	memFree(puddle->vertices);
}
