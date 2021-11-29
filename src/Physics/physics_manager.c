#include <Physics/physics_manager.h>
#include <Kernel/Memory/memory.h>

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
