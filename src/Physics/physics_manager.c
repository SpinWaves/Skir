#include <Physics/physics_manager.h>
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

static Physics_Engine __pm;

void initPhysicsManager()
{
    initPhysicsEngine(&__pm);
}
void pm_addCollider(BoxCollider* collider)
{
    addCollider(&__pm, collider);
}
void pm_checkCollisions()
{
    checkCollisions(&__pm);
}
void shutdownPhysicsManager()
{
    shutdownPhysicsEngine(&__pm);
}
