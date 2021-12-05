// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

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
