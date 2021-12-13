// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __TEXT__
#define __TEXT__

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

typedef struct
{
    char* text;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Color color;
} Text;

extern TTF_Font* default_font;

void initText(Text* t, SDL_Renderer* renderer, const char* text, SDL_Color* color, TTF_Font* font);
void scaleText(Text* t, int x, int y, int w, int h);
void updateText(Text* t, SDL_Renderer* renderer, const char* text);
void renderText(Text* t, SDL_Renderer* renderer);
void deleteText(Text* t);

#endif // __TEXT__
