// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/text.h>
#include <Kernel/log.h>

TTF_Font* default_font = NULL;

lines_texture* generate_texture(Text* t, SDL_Renderer* renderer, const char* text)
{
    lines_texture* tex = custom_malloc(sizeof(lines_texture));
    SDL_Surface* surface = TTF_RenderUTF8_Blended(t->font, text, t->color);
    if(!surface)
        log_report(ERROR, "Text: unable to create surface from text : %s", text);
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface); // Segmentation fault
    if(!tex->texture)
        log_report(ERROR, "Text: unable to create texture from surface : %s", text);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(tex->texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };
    tex->rect = dstrect;
    tex->next = NULL;
    SDL_FreeSurface(surface);
    return tex;
}

void add_line(Text* t, lines_texture* line)
{
    lines_texture* buffer = t->texts;
    if(buffer == NULL)
    {
        t->texts = line;
        return;
    }
    while(buffer->next != NULL)
        buffer = buffer->next;
    buffer->next = line;
}

void initText(Text* t, SDL_Renderer* renderer, const char* text, SDL_Color* color, TTF_Font* font)
{
    t->text = text;
    t->font = font;
    t->color = *color;
    if(font == NULL)
        log_report(FATAL_ERROR, "Text: font is NULL");

    char* finder = strstr(text, "\n");
    if(finder == NULL)
        t->texts = generate_texture(t, renderer, text);
    else
    {
        int len = strlen(text);
        int pos = -1;
        char* part = NULL;
        while(finder != NULL)
        {
            finder = strstr(text + pos + 1, "\n");
            strncpy(part, text + pos + 1, finder - pos);
            printf("%s\n", part);
            pos = (int)(text + len - 1 - finder);
            add_line(t, generate_texture(t, renderer, part));
        }
    }
}
void scaleText(Text* t, int x, int y, int w, int h)
{
   // SDL_Rect rect = {x, y, w, h};
   // t->rect = rect;
}
void updateText(Text* t, SDL_Renderer* renderer, const char* text)
{
    char* finder = strstr(text, "\n");
    if(finder == NULL)
        t->texts = generate_texture(t, renderer, text);
    else
    {
        int len = strlen(text);
        int pos = -1;
        char* part = NULL;
        while(finder != NULL)
        {
            finder = strstr(text + pos + 1, "\n");
            strncpy(part, text + pos + 1, finder - pos);
            printf("%s\n", part);
            pos = (int)(text + len - 1 - finder);
            add_line(t, generate_texture(t, renderer, part));
        }
    }
}
void renderText(Text* t, SDL_Renderer* renderer)
{
    lines_texture* buffer = t->texts;
    while(buffer != NULL)
    {
        if(t->texts->next != NULL)
            buffer->rect.y += TTF_FontLineSkip(t->font);

        SDL_RenderCopy(renderer, buffer->texture, NULL, &buffer->rect);
        buffer = buffer->next;
    }
}
void deleteText(Text* t)
{
    lines_texture* buffer = t->texts;
    lines_texture* double_buffer = NULL;
    while(buffer != NULL)
    {
        double_buffer = buffer->next;
        SDL_DestroyTexture(buffer->texture);
        custom_free(buffer);
        buffer = double_buffer;
    }
}
