// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <GUI/about.h>
#include <IO/system_files.h>

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
    SDL_Color white = { 255, 255, 255};
    initText(__about_page->text, renderer, get_config_value("about_text"), &white, default_font);
    setPosText(__about_page->text, 20, 300);
    __about_page->back = createButton(renderer, get_config_value("back"), 50, height / 8, width - 100, height / 10, 75, 75, 75);
    setFunctionCall(__about_page->back, hangUpAboutPage);
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
    renderButton(__about_page->back);
}
void shutdownAboutPage()
{
    shutdownAboutPage();
    deleteText(__about_page->text);
    custom_free(__about_page->text);
    destroyButton(__about_page->back);
    custom_free(__about_page->back);

    custom_free(__about_page);
}
