#ifndef __PHYSICS_ENGINE__
#define __PHYSICS_ENGINE__

#include <stdbool.h>

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    bool is_colliding;
} BoxCollider;

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
void checkCollisions(Physics_Engine* engine);
void shutdownPhysicsEngine(Physics_Engine* engine);

#endif // __PHYSICS_ENGINE__
