// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <GUI/about.h>
#include <IO/system_files.h>

#include <SDL2/SDL_image.h>

typedef struct
{
    Button* back;
    Text* text;
    bool is_called;
    SDL_Renderer* renderer;
    Sprite* logo;
} About_Page;

static About_Page* __about_page = NULL;

void initAboutPage(SDL_Renderer* renderer, int width, int height)
{
    __about_page = memAlloc(sizeof(About_Page));
    __about_page->is_called = false;
    __about_page->renderer = renderer;
    __about_page->text = memAlloc(sizeof(Text));
    SDL_Color white = { 255, 255, 255 };

    TTF_Font* font = TTF_OpenFont(MAIN_DIR"ressources/fonts/retro_gaming.ttf", 20);
    if(font == NULL)
        log_report(FATAL_ERROR, "About page: cannot open font");

    initTextKey(__about_page->text, renderer, "about_text", &white, font, CENTER);
    setPosText(__about_page->text, (width / 2) - (__about_page->text->texts->rect.w / 2), 300);

	SDL_Texture* texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/plank_0.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "About page : unable to create texture : "MAIN_DIR"ressources/Assets/UI/plank_0.png");
    __about_page->back = createButtonTextured(renderer, "back", width / 3, height - height / 4, width / 3, height / 10, createSprite(renderer, texture, 0, 0, 0, 0), 30, true);
    setFunctionCall(__about_page->back, hangUpAboutPage);

	texture = IMG_LoadTexture(renderer, MAIN_DIR"ressources/Assets/UI/spinwaves.png");
	if(texture == NULL)
		log_report(FATAL_ERROR, "About page : unable to create texture : "MAIN_DIR"ressources/Assets/UI/spinwaves.png");
    int w;
    int h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    w /= 2;
    h /= 2;
    __about_page->logo = createSprite(renderer, texture, __about_page->text->texts->rect.x + __about_page->text->texts->rect.w + 5, __about_page->text->texts->rect.y - h / 2, w, h);
    __about_page->logo->day_night_cycle = false;
}

inline void callAboutPage()
{
    __about_page->is_called = true;
}

inline void hangUpAboutPage()
{
    __about_page->is_called = false;
}

inline bool isAboutPageCalled()
{
    return __about_page->is_called;
}

void updateAboutPage(Inputs *in)
{
    updateButton(__about_page->back, in);
}

void renderAboutPage()
{
    renderText(__about_page->text, __about_page->renderer);
    renderSprite(__about_page->logo);
    renderButton(__about_page->back);
}

void shutdownAboutPage()
{
    destroySprite(__about_page->logo);
    deleteText(__about_page->text);
    memFree(__about_page->text);
    destroyButton(__about_page->back);
    memFree(__about_page->back);

    memFree(__about_page);
}
