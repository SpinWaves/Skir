// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <GUI/main_menu.h>
#include <IO/system_files.h>

typedef struct
{
    Button* butts[3];
    Text* texts[2];
    Sprite* bg;
    bool is_called;
    SDL_Renderer* renderer;
} Main_Menu;

static Main_Menu* __menu = NULL;

void play_button()
{
    __menu->butts[0]->is_activated = false;
    hangUpMainMenu();
}
void settings_button()
{
}
void about_button()
{
    callAboutPage();
}

void initMainMenu(SDL_Renderer* renderer, int width, int height)
{
    __menu = memAlloc(sizeof(Main_Menu));
    __menu->bg = memAlloc(sizeof(Sprite));
    __menu->renderer = renderer;
    for(int i = 0; i < sizeof(__menu->texts) / sizeof(__menu->texts[0]); i++)
        __menu->texts[i] = memAlloc(sizeof(Text));
    const char* buttons_texts[] = { get_config_value("play"), get_config_value("settings"), get_config_value("about") };
    void (*buttons_tasks[])() = {play_button, settings_button, about_button};
    for(int i = 0; i < sizeof(__menu->butts) / sizeof(__menu->butts[0]); i++)
    {
        __menu->butts[i] = createButton(renderer, buttons_texts[i], width / 4, (height / 8) * (i + 1) + height / 5, width / 2, height / 10, 75, 75, 75);
        setFunctionCall(__menu->butts[i], buttons_tasks[i]);
    }

    initAboutPage(renderer, width, height);
}
void callMainMenu()
{
    __menu->is_called = true;
}
void hangUpMainMenu()
{
    __menu->is_called = false;
}
bool isMainMenuCalled()
{
    return __menu->is_called;
}
void updateMainMenu(Inputs *in)
{
    if(isAboutPageCalled())
        updateAboutPage(in);
    else
    {
        //for(int i = 0; i < sizeof(__menu->texts) / sizeof(__menu->texts[0]); i++)
        //    update
        for(int i = 0; i < sizeof(__menu->butts) / sizeof(__menu->butts[0]); i++)
            updateButton(__menu->butts[i], in);
    }
}
void renderMainMenu()
{
    if(isAboutPageCalled())
        renderAboutPage();
    else
    {
        for(int i = 0; i < sizeof(__menu->butts) / sizeof(__menu->butts[0]); i++)
            renderButton(__menu->butts[i]);
    }
}
void shutdownMainMenu()
{
    for(int i = 0; i < sizeof(__menu->texts) / sizeof(__menu->texts[0]); i++)
    {
        deleteText(__menu->texts[i]);
        memFree(__menu->texts[i]);
    }
    for(int i = 0; i < sizeof(__menu->butts) / sizeof(__menu->butts[0]); i++)
    {
        destroyButton(__menu->butts[i]);
        memFree(__menu->butts[i]);
    }

    memFree(__menu);
}
