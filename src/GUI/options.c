// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <GUI/options.h>
#include <IO/system_files.h>
#include <Utils/utils.h>

#include <SDL2/SDL_image.h>

typedef struct
{
    Button* back;
    bool is_called;
    SDL_Renderer* renderer;
    Sprite* pop_up_bg;
    Sprite* cross;
    Button* butts[2];
    Button* lang_butts[2];
} Options_Page;

static Options_Page* __options_page = NULL;

static bool pop_up_lang = false;
static int active_lang = 0;

void lang_pop_up()
{
    pop_up_lang = !pop_up_lang;
}

extern bool print_fps;

void printFPS()
{
    print_fps = !print_fps;
}

void initOptionsPage(SDL_Renderer* renderer, int width, int height)
{
    __options_page = memAlloc(sizeof(Options_Page));
    __options_page->is_called = false;
    __options_page->renderer = renderer;

	SDL_Texture* texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/plank_1.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "Options page : unable to create texture : "MAIN_DIR"ressources/Assets/UI/plank_1.png");
    
    SDL_SetTextureColorMod(texture, 130, 110, 120);
    __options_page->pop_up_bg = createSprite(renderer, texture, 150 + width / 3, height / 10 - 50, 300, 380);
    __options_page->pop_up_bg->day_night_cycle = false;
    __options_page->pop_up_bg->angle = -90.0;

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/cross.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "Options page : unable to create texture : "MAIN_DIR"ressources/Assets/UI/cross.png");
    
    __options_page->cross = createSprite(renderer, texture, 0, 0, 48, 48);
    __options_page->cross->day_night_cycle = false;

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/plank_0.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "Options page : unable to create texture : "MAIN_DIR"ressources/Assets/UI/plank_0.png");
    __options_page->back = createButtonTextured(renderer, "back", width / 3, height - height / 4, width / 3, height / 10, createSprite(renderer, texture, 0, 0, 0, 0), 30, true);
    setFunctionCall(__options_page->back, hangUpOptionsPage);

    const char* buttons_texts[] = { "lang", "print_fps" };
    void (*buttons_tasks[])() = { lang_pop_up, printFPS };

    for(int i = 0; i < ARRAY_SIZE(__options_page->butts); i++)
    {
        __options_page->butts[i] = createButtonTextured(renderer, buttons_texts[i], 50, 100 + (height / 8) * (i + 1), width / 3, height / 10, createSprite(renderer, texture, 50, 100 + (height / 8) * (i + 1), width / 3, height / 10), 30, true);
        __options_page->butts[i]->sprite->angle = sin((i + 1) * 2);
        setFunctionCall(__options_page->butts[i], buttons_tasks[i]);
    }

    const char* lang_buttons_texts[] = { "English", "Français" };

    for(int i = 0; i < ARRAY_SIZE(__options_page->lang_butts); i++)
    {
        __options_page->lang_butts[i] = createButtonTextured(renderer, lang_buttons_texts[i], 150 + width / 3, 30 + (height / 10) * (i + 1), 250, 50, createSprite(renderer, texture, 150 + width / 3, 30 + (height / 10) * (i + 1), 250, 50), 20, false);
        __options_page->lang_butts[i]->sprite->angle = sin((i + 1) * 2) * 2;
    }
}

inline void callOptionsPage()
{
    __options_page->is_called = true;
}

inline void hangUpOptionsPage()
{
    __options_page->is_called = false;
}

inline bool isOptionsPageCalled()
{
    return __options_page->is_called;
}

static const char* langs[] = {
    MAIN_DIR"Languages/en.cfg",
    MAIN_DIR"Languages/fr.cfg",
};

void updateOptionsPage(Inputs *in)
{
    updateButton(__options_page->back, in);
    for(int i = 0; i < ARRAY_SIZE(__options_page->butts); i++)
        updateButton(__options_page->butts[i], in);

    if(pop_up_lang)
    {
        for(int i = 0; i < ARRAY_SIZE(__options_page->lang_butts); i++)
        {
            updateButton(__options_page->lang_butts[i], in);
            if(__options_page->lang_butts[i]->is_released)
            {
                active_lang = i;
                openConfigFile(langs[i]);
            }
        }
    }
}

void renderOptionsPage()
{
    renderButton(__options_page->back);
    for(int i = 0; i < ARRAY_SIZE(__options_page->butts); i++)
        renderButton(__options_page->butts[i]);
    if(pop_up_lang)
    {
        renderRotateSprite(__options_page->pop_up_bg);
        for(int i = 0; i < ARRAY_SIZE(__options_page->lang_butts); i++)
            renderButton(__options_page->lang_butts[i]);
        __options_page->cross->coords->x = __options_page->lang_butts[active_lang]->sprite->coords->x + __options_page->lang_butts[active_lang]->sprite->coords->w + 20;
        __options_page->cross->coords->y = __options_page->lang_butts[active_lang]->sprite->coords->y;
        renderSprite(__options_page->cross);
    }
}

void shutdownOptionsPage()
{
    for(int i = 0; i < ARRAY_SIZE(__options_page->butts); i++)
        destroySprite(__options_page->butts[i]);
    for(int i = 0; i < ARRAY_SIZE(__options_page->lang_butts); i++)
        destroyButton(__options_page->lang_butts[i]);
    destroySprite(__options_page->pop_up_bg);
    destroySprite(__options_page->cross);
    destroyButton(__options_page->back);
    memFree(__options_page->back);

    memFree(__options_page);
}
