#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

#include <Physics/physics_engine.h>

void initPhysicsManager();
void pm_addCollider(BoxCollider* collider);
void pm_checkCollisions();
void shutdownPhysicsManager();

#endif // __PHYSICS_MANAGER__
