// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __PHYSICS_ENGINE__
#define __PHYSICS_ENGINE__

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    bool left_collision;
    bool right_collision;
    bool top_collision;
    bool bottom_collision;

    bool important_collider;

    int collider_id;
} BoxCollider;

BoxCollider* newBoxCollider(int x, int y, int w, int h, bool important_collider);
void freeBoxCollider(BoxCollider* boxCollider);

typedef struct colliders_node
{
    BoxCollider* collider;
    struct colliders_node* next;
} colliders_node;

typedef struct
{
    colliders_node* head;
} Physics_Engine;

void initPhysicsEngine(Physics_Engine* engine);
void addCollider(Physics_Engine* engine, BoxCollider* collider);
void checkCollisions(Physics_Engine* engine, SDL_Renderer* renderer, bool drawHideBoxes);
void checkCollisionsCollider(Physics_Engine* engine, BoxCollider* collider);
void checkCollisionsColliderWithID(Physics_Engine* engine, BoxCollider* collider, int id);
void shutdownPhysicsEngine(Physics_Engine* engine);

#endif // __PHYSICS_ENGINE__
