// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#include <GUI/main_menu.h>

static Main_Menu* __menu = NULL;

void initMainMenu()
{
    __menu = custom_malloc(sizeof(Main_Menu));
    __menu->bg = custom_malloc(sizeof(Sprite));
    for(int i = 0; i < sizeof(__menu->texts) / sizeof(__menu->texts[0]); i++)
        __menu->texts[i] = custom_malloc(sizeof(Text));
    for(int i = 0; i < sizeof(__menu->butts) / sizeof(__menu->butts[0]); i++)
        __menu->butts[i] = custom_malloc(sizeof(Button));
    __menu->font = TTF_OpenFont(MAIN_DIR"src/fonts/OpenSans-Regular.ttf", 15);
}
void callMainMenu()
{
    __menu->is_called = true;
}
void hangUpMainMenu()
{
    __menu->is_called = false;
}
void updateMainMenu()
{

}
void renderMainMenu()
{

}
void shutdownMainMenu()
{
    custom_free(__menu)
}
