// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __BUTTON__
#define __BUTTON__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include <Kernel/text.h>
#include <Kernel/sprite.h>
#include <IO/inputs.h>

typedef struct
{
    SDL_Rect* coords;
    bool is_activated;
    bool trigger;
    void (*f)();
    SDL_Color* color;
    Text* text;
    SDL_Renderer* renderer;
    Sprite* sprite;
    TTF_Font* font;
} Button;

Button* createButton(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h, int r, int g, int b, int font_size);
Button* createButtonTextured(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h, Sprite* sprite, int font_size);
void setFunctionCall(Button* button, void (*f)());
bool isDown(Button* button);
void renderButton(Button* button);
void updateButton(Button* button, Inputs* intpus);
void destroyButton(Button* button);

#endif // __BUTTON__
