// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __TEXT__
#define __TEXT__

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

typedef enum { LEFT, CENTER, RIGHT } alignment;

typedef struct lines_texture
{
    SDL_Texture* texture;
    SDL_Rect rect;
    struct lines_texture* next;
} lines_texture;

typedef struct
{
    char* text;
    TTF_Font* font;
    lines_texture* texts;
    SDL_Color color;
    int x;
    int y;
    alignment align;
} Text;

extern TTF_Font* default_font;

void initText(Text* t, SDL_Renderer* renderer, const char* text, SDL_Color* color, TTF_Font* font, alignment align);
void scaleText(Text* t, int x, int y, int w, int h);
void setPosText(Text* t, int x, int y);
void updateText(Text* t, SDL_Renderer* renderer, const char* text);
void renderText(Text* t, SDL_Renderer* renderer);
void deleteText(Text* t);

#endif // __TEXT__
