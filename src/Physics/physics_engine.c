// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#include <Physics/physics_engine.h>
#include <Kernel/Memory/memory.h>

BoxCollider* newBoxCollider(int x, int y, int w, int h)
{
    BoxCollider* box = custom_malloc(sizeof(BoxCollider));
    box->x = x;
    box->y = y;
    box->w = w;
    box->h = h;
    box->is_colliding = false;
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
void checkCollisions(Physics_Engine* engine)
{
    colliders_node* buffer = engine->head;
    while(buffer != NULL)
    {
        if(buffer->next != NULL)
        {
            /* AABB collision detection */
            if( buffer->collider->x < buffer->next->collider->x + buffer->next->collider->w &&
                buffer->collider->x + buffer->collider->w > buffer->next->collider->x       &&
                buffer->collider->y < buffer->next->collider->y + buffer->next->collider->h &&
                buffer->collider->y + buffer->collider->h > buffer->next->collider->y          )
            {
                buffer->collider->is_colliding = true;
                buffer->next->collider->is_colliding = true;
            }
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
