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

	puddle->points = (WaterPoint**)memAlloc(sizeof(WaterPoint*) * puddle->w);
	if(puddle->points == NULL)
		log_report(FATAL_ERROR, "Water Puddle : unable to alloc memory for points");

	puddle->vertices = (SDL_Vertex**)memAlloc(sizeof(SDL_Vertex*) * (puddle->w * 6));
	if(puddle->vertices == NULL)
		log_report(FATAL_ERROR, "Water Puddle : unable to alloc memory for vertices");

/*
Vector2 p1 = new Vector2((i - 1) * scale, springs[i - 1].Height);
Vector2 p2 = new Vector2(i * scale, springs[i].Height);
Vector2 p3 = new Vector2(p2.X, bottom);
Vector2 p4 = new Vector2(p1.X, bottom);

primitiveBatch.AddVertex(p1, lightBlue);
primitiveBatch.AddVertex(p2, lightBlue);
primitiveBatch.AddVertex(p3, midnightBlue);

primitiveBatch.AddVertex(p1, lightBlue);
primitiveBatch.AddVertex(p3, midnightBlue);
primitiveBatch.AddVertex(p4, midnightBlue);
*/
	int v = 0;
	for(int i = 0; i < puddle->w; i++)
	{
		puddle->points[i] = memAlloc(sizeof(WaterPoint));
		puddle->points[i]->position.x = x + i;
		puddle->points[i]->position.y = y;
		puddle->points[i]->velocity = 0.0f;
 
		puddle->vertices[v] = memAlloc(sizeof(SDL_Vertex));
		puddle->vertices[v]->position.x = puddle->points[i]->position.x;
		puddle->vertices[v]->position.y = puddle->points[i]->position.y;
		puddle->vertices[v]->color.r = 94; puddle->vertices[v]->color.g = 189; puddle->vertices[v]->color.b = 247; puddle->vertices[v]->color.a = 128;
		v++;
		puddle->vertices[v] = memAlloc(sizeof(SDL_Vertex));
		puddle->vertices[v]->position.x = puddle->points[i]->position.x + 1;
		puddle->vertices[v]->position.y = puddle->points[i]->position.y;
		puddle->vertices[v]->color.r = 94; puddle->vertices[v]->color.g = 189; puddle->vertices[v]->color.b = 247; puddle->vertices[v]->color.a = 128;
		v++;
		puddle->vertices[v] = memAlloc(sizeof(SDL_Vertex));
		puddle->vertices[v]->position.x = puddle->points[i]->position.x + 1;
		puddle->vertices[v]->position.y = puddle->points[i]->position.y + h;
		puddle->vertices[v]->color.r = 94; puddle->vertices[v]->color.g = 189; puddle->vertices[v]->color.b = 247; puddle->vertices[v]->color.a = 128;

		v++;
		puddle->vertices[v] = memAlloc(sizeof(SDL_Vertex));
		puddle->vertices[v]->position.x = puddle->points[i]->position.x;
		puddle->vertices[v]->position.y = puddle->points[i]->position.y;
		puddle->vertices[v]->color.r = 94; puddle->vertices[v]->color.g = 189; puddle->vertices[v]->color.b = 247; puddle->vertices[v]->color.a = 128;
		v++;
		puddle->vertices[v] = memAlloc(sizeof(SDL_Vertex));
		puddle->vertices[v]->position.x = puddle->points[i]->position.x + 1;
		puddle->vertices[v]->position.y = puddle->points[i]->position.y + h;
		puddle->vertices[v]->color.r = 94; puddle->vertices[v]->color.g = 189; puddle->vertices[v]->color.b = 247; puddle->vertices[v]->color.a = 128;
		v++;
		puddle->vertices[v] = memAlloc(sizeof(SDL_Vertex));
		puddle->vertices[v]->position.x = puddle->points[i]->position.x;
		puddle->vertices[v]->position.y = puddle->points[i]->position.y + h;
		puddle->vertices[v]->color.r = 94; puddle->vertices[v]->color.g = 189; puddle->vertices[v]->color.b = 247; puddle->vertices[v]->color.a = 128;
		v++;
	}
}

void updateWaterPuddle(WaterPuddle* puddle)
{
	/*
	for(int i = 0; i < puddle->w; i++)
	{
		puddle->points[i]->position.x = puddle->x + i * puddle->w;
		puddle->points[i]->position.y = puddle->y;

		puddle->vertices[i]->position.x = puddle->points[i]->position.x;
		puddle->vertices[i]->position.y = puddle->points[i]->position.y;
	}
	*/
}

void renderWaterPuddle(WaterPuddle* puddle, SDL_Renderer* renderer)
{
	for(int i = 0; i < puddle->w; i++)
		SDL_RenderGeometry(renderer, NULL, puddle->vertices[i * 3], 3, NULL, 0);
}

void destroyWaterPuddle(WaterPuddle* puddle)
{
	for(int i = 0; i < puddle->w; i++)
	{
		memFree(puddle->points[i]);
		for(int j = 0; j < 6; j++)
			memFree(puddle->vertices[(i * 6) + j]);
	}

	memFree(puddle->points);
	memFree(puddle->vertices);
}
