// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include <Kernel/text.h>
#include <IO/inputs.h>

typedef struct
{
    SDL_Rect* coords;
    bool is_activated;
    bool trigger;
    void (*f)();
    SDL_Color* color;
    Text* text;
    TTF_Font* font;
    SDL_Renderer* renderer;
} Button;

Button* createButton(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h, int r, int g, int b);
void setFunctionCall(Button* button, void (*f)());
bool isDown(Button* button);
void renderButton(Button* button);
void updateButton(Button* button, Inputs* intpus);
void destroyButton(Button* button);

#endif // __BUTTON__
