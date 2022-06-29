// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

#include <Physics/physics_engine.h>
#include <stdbool.h>

void initPhysicsManager();
void pm_addCollider(BoxCollider* collider);
void pm_checkCollisions(SDL_Renderer* renderer, bool drawHideBoxes);
void pm_checkCollisionsCollider(BoxCollider* collider);
void pm_checkCollisionsColliderWithID(BoxCollider* collider, int id);
void shutdownPhysicsManager();

#endif // __PHYSICS_MANAGER__
