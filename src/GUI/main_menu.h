// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <Kernel/kernel.h>

void initMainMenu(SDL_Renderer* renderer, int width, int height);
void callMainMenu();
void hangUpMainMenu();
bool isMainMenuCalled();
void updateMainMenu(Inputs *in);
void renderMainMenu();
void shutdownMainMenu();

#endif // __MAIN_MENU__
