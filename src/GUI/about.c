// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <GUI/about.h>

typedef struct
{
    Button* back;
    Text* text;
    bool is_called;
    SDL_Renderer* renderer;
} About_Page;

static About_Page* __about_page = NULL;

void initAboutPage(SDL_Renderer* renderer, int width, int height)
{
    __about_page = custom_malloc(sizeof(About_Page));
    __about_page->is_called = false;
    __about_page->renderer = renderer;
    __about_page->text = custom_malloc(sizeof(Text));
    const char* text = NULL;
    SDL_Color white = { 255, 255, 255};
    initText(__about_page->text, renderer, text, &white, default_font);
    __about_page->back = createButton(renderer, "Back", 50, height / 8, width - 100, height / 10, 75, 75, 75);
    setFunctionCall(__about_page->back, hangUpAboutPage);
}
void callAboutPage()
{
    __about_page->is_called = true;
}
void hangUpAboutPage()
{
    __about_page->is_called = false;
}
bool isAboutPageCalled()
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
    renderButton(__about_page->back);
}
void shutdownAboutPage()
{
    deleteText(__about_page->text);
    custom_free(__about_page->text);
    destroyButton(__about_page->back);
    custom_free(__about_page->back);

    custom_free(__about_page);
}
