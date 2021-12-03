// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <GUI/button.h>
#include <Kernel/kernel.h>

typedef struct
{
    Buttons* butts[3];
    Text* texts[2];
    Sprite* bg;
    TTF_font* font;
    bool is_called;
} Main_Menu;

void initMainMenu();
void callMainMenu();
void hangUpMainMenu():
void updateMainMenu();
void renderMainMenu();
void shutdownMainMenu();

#endif // __MAIN_MENU__
