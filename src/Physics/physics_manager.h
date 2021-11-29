#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

#include <Physics/physics_engine.h>

BoxCollider* newBoxCollider(int x, int y, int w, int h);
void freeBoxCollider(BoxCollider* boxCollider);

void initPhysicsManager();
void pm_addCollider(BoxCollider* collider);
void pm_checkCollisions();
void shutdownPhysicsManager();

#endif // __PHYSICS_MANAGER__
