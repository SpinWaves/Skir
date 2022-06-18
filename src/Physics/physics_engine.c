// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Physics/physics_engine.h>
#include <Kernel/Memory/memory.h>

BoxCollider* newBoxCollider(int x, int y, int w, int h, bool important_collider)
{
    BoxCollider* box = custom_malloc(sizeof(BoxCollider));
    
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
    custom_free(boxCollider);
}

void initPhysicsEngine(Physics_Engine* engine)
{
    engine->head = NULL;
}

void addCollider(Physics_Engine* engine, BoxCollider* collider)
{
    colliders_node* new_node = custom_malloc(sizeof(colliders_node));
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
        if( collider->x <= buffer->collider->x + buffer->collider->w &&
            collider->y <= buffer->collider->y + buffer->collider->h &&
            collider->y + collider->h >= buffer->collider->y)
            collider->left_collision = true;

        if( collider->x + collider->w >= buffer->collider->x  &&
            collider->y <= buffer->collider->y + buffer->collider->h &&
            collider->y + collider->h >= buffer->collider->y)
            collider->right_collision = true;

        if( collider->y <= buffer->collider->y + buffer->collider->h &&
            collider->x < buffer->collider->x + buffer->collider->w &&
            collider->x + collider->w > buffer->collider->x)
            collider->top_collision = true;

        if( collider->y + collider->h >= buffer->collider->y  &&
            collider->x < buffer->collider->x + buffer->collider->w &&
            collider->x + collider->w > buffer->collider->x)
            collider->bottom_collision = true;

        buffer = buffer->next;
    }
}

void checkCollisions(Physics_Engine* engine)
{
    colliders_node* buffer = engine->head;
    colliders_node* buffer2 = engine->head;
    while(buffer != NULL)
    {
        if(!buffer->collider->important_collider)
        {
            buffer = buffer->next;
            continue;
        }

        buffer->collider->left_collision = false;
        buffer->collider->right_collision = false;
        buffer->collider->top_collision = false;
        buffer->collider->bottom_collision = false;

        buffer2 = engine->head;

        while(buffer2 != NULL)
        {
            if(buffer2 == buffer)
            {
                buffer2 = buffer2->next;
                continue;
            }

            /* AABB collision detection */
            if( buffer->collider->x < buffer2->collider->x + buffer2->collider->w &&
                buffer->collider->y < buffer2->collider->y + buffer2->collider->h - 5 &&
                buffer->collider->y + buffer->collider->h > buffer2->collider->y + 5)
                buffer->collider->left_collision = true;

            if( buffer->collider->x + buffer->collider->w > buffer2->collider->x  &&
                buffer->collider->y < buffer2->collider->y + buffer2->collider->h - 5 &&
                buffer->collider->y + buffer->collider->h > buffer2->collider->y + 5)
                buffer->collider->right_collision = true;

            if( buffer->collider->y < buffer2->collider->y + buffer2->collider->h &&
                buffer->collider->x < buffer2->collider->x + buffer2->collider->w &&
                buffer->collider->x + buffer->collider->w > buffer2->collider->x)
                buffer->collider->top_collision = true;

            if( buffer->collider->y + buffer->collider->h > buffer2->collider->y  &&
                buffer->collider->x < buffer2->collider->x + buffer2->collider->w &&
                buffer->collider->x + buffer->collider->w > buffer2->collider->x)
                buffer->collider->bottom_collision = true;

            buffer2 = buffer2->next;
        }

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
        custom_free(buffer);
        buffer = double_buffer;
    }
}
