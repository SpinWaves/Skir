// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <GUI/main_menu.h>
#include <IO/system_files.h>
#include <Utils/utils.h>
#include <Kernel/kernel.h>

#include <SDL2/SDL_image.h>

typedef struct
{
    Button* butts[4];
    Text* version;
    Sprite* bg;
    bool is_called;
    SDL_Renderer* renderer;
    Sprite* title;
} Main_Menu;

static Main_Menu* __menu = NULL;

void play_button()
{
    __menu->butts[0]->is_activated = false;
    hangUpMainMenu();
}

void settings_button()
{
    callOptionsPage();
}

void about_button()
{
    callAboutPage();
}

extern Application app;

void quit()
{
    app.run = false;
}

void initMainMenu(SDL_Renderer* renderer, int width, int height)
{
    __menu = memAlloc(sizeof(Main_Menu));
    __menu->bg = memAlloc(sizeof(Sprite));
    __menu->renderer = renderer;
     __menu->version = memAlloc(sizeof(Text));
    const char* buttons_texts[] = { get_config_value("play"), get_config_value("settings"), get_config_value("about"), get_config_value("quit") };
    void (*buttons_tasks[])() = { play_button, settings_button, about_button, quit };

	SDL_Texture* texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/plank_0.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "Main menu : unable to create texture : "MAIN_DIR"ressources/Assets/UI/plank_0.png");
    for(int i = 0; i < ARRAY_SIZE(__menu->butts); i++)
    {
        __menu->butts[i] = createButtonTextured(renderer, buttons_texts[i], 50, (height / 8) * (i + 1) + (height - 50 - (height / 8) * (ARRAY_SIZE(__menu->butts) + 1)), width / 3, height / 10, createSprite(renderer, texture, 0, 0, 0, 0), 30);
        __menu->butts[i]->sprite->angle = sin((i + 1) * 2);
        setFunctionCall(__menu->butts[i], buttons_tasks[i]);
    }

    SDL_Color white = { 255, 255, 255 };
    initText(__menu->version, renderer, get_config_value("version"), &white, default_font, LEFT);
    setPosText(__menu->version, width - 30 - __menu->version->texts->rect.w, height - 30);

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/logo.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "Main menu : unable to create texture : "MAIN_DIR"ressources/Assets/UI/logo.png");
    __menu->title = createSprite(renderer, texture, (width / 2) - 256, 50, 512, 180);
    __menu->title->day_night_cycle = false;

    initAboutPage(renderer, width, height);
    initOptionsPage(renderer, width, height);
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
    else if(isOptionsPageCalled())
        updateOptionsPage(in);
    else
    {
        for(int i = 0; i < ARRAY_SIZE(__menu->butts); i++)
            updateButton(__menu->butts[i], in);
    }
}

void renderMainMenu()
{
    if(isAboutPageCalled())
        renderAboutPage();
    else if(isOptionsPageCalled())
        renderOptionsPage();
    else
    {
        renderRotateSprite(__menu->title);
        renderText(__menu->version, __menu->renderer);
        for(int i = 0; i < ARRAY_SIZE(__menu->butts); i++)
            renderButton(__menu->butts[i]);
    }
}

void shutdownMainMenu()
{
    deleteText(__menu->version);
    memFree(__menu->version);
    for(int i = 0; i < ARRAY_SIZE(__menu->butts); i++)
    {
        destroyButton(__menu->butts[i]);
        memFree(__menu->butts[i]);
    }

    destroySprite(__menu->title);

    shutdownAboutPage();
    shutdownOptionsPage();

    memFree(__menu);
}
