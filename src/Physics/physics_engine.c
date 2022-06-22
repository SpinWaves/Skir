// Copyright (C) 5021 - 5022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Physics/physics_engine.h>
#include <Kernel/Memory/memory.h>

BoxCollider* newBoxCollider(int x, int y, int w, int h, bool important_collider)
{
    BoxCollider* box = memAlloc(sizeof(BoxCollider));
    
    box->x = x;
    box->y = y;
    box->w = w;
    box->h = h;
    
    box->left_collision = false;
    box->right_collision = false;
    box->top_collision = false;
    box->bottom_collision = false;
    
    box->important_collider = important_collider;

    return box;
}

inline void freeBoxCollider(BoxCollider* boxCollider)
{
    memFree(boxCollider);
}

void initPhysicsEngine(Physics_Engine* engine)
{
    engine->head = NULL;
}

void addCollider(Physics_Engine* engine, BoxCollider* collider)
{
    colliders_node* new_node = memAlloc(sizeof(colliders_node));
    new_node->collider = collider;
    new_node->next = engine->head;
    engine->head = new_node;
}

void checkCollisionsCollider(Physics_Engine* engine, BoxCollider* collider)
{
    collider->left_collision = false;
    collider->right_collision = false;
    collider->top_collision = false;
    collider->bottom_collision = false;

    colliders_node* buffer = engine->head;

    while(buffer != NULL)
    {
        if(buffer->collider == collider)
        {
            buffer = buffer->next;
            continue;
        }

        /* AABB collision detection */
        if( collider->x < buffer->collider->x + buffer->collider->w &&
            collider->x + collider->w > buffer->collider->x + 1 &&
            collider->y < buffer->collider->y + buffer->collider->h - 5 &&
            collider->y + collider->h > buffer->collider->y + 5)
            collider->left_collision = true;

        if( collider->x + collider->w > buffer->collider->x &&
            collider->x < buffer->collider->x &&
            collider->y < buffer->collider->y + buffer->collider->h - 5 &&
            collider->y + collider->h > buffer->collider->y + 5)
            collider->right_collision = true;

        if( collider->y < buffer->collider->y + buffer->collider->h &&
            collider->y + collider->h > buffer->collider->y + buffer->collider->h &&
            collider->x < buffer->collider->x + buffer->collider->w - 7 &&
            collider->x + collider->w > buffer->collider->x + 7)
            collider->top_collision = true;

        if( collider->y + collider->h > buffer->collider->y &&
            collider->y < buffer->collider->y &&
            collider->x < buffer->collider->x + buffer->collider->w - 7 &&
            collider->x + collider->w > buffer->collider->x + 7)
            collider->bottom_collision = true;

        buffer = buffer->next;
    }
}

void checkCollisions(Physics_Engine* engine, SDL_Renderer* renderer, bool drawHideBoxes)
{
    colliders_node* buffer = engine->head;
    while(buffer != NULL)
    {
        if(drawHideBoxes)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect rect = { buffer->collider->x, buffer->collider->y, buffer->collider->w, buffer->collider->h };
            SDL_RenderDrawRect(renderer, &rect);
        }

        if(!buffer->collider->important_collider)
        {
            buffer = buffer->next;
            continue;
        }

        checkCollisionsCollider(engine, buffer->collider);

        buffer = buffer->next;
    }
}

void shutdownPhysicsEngine(Physics_Engine* engine)
{
    colliders_node* buffer = engine->head;
    colliders_node* double_buffer = NULL;
    while(buffer != NULL)
    {
        double_buffer = buffer->next;
        memFree(buffer);
        buffer = double_buffer;
    }
}
