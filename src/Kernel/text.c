// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/text.h>
#include <Kernel/log.h>
#include <Kernel/Memory/memory.h>
#include <string.h>

TTF_Font* default_font = NULL;

lines_texture* generate_texture(Text* t, SDL_Renderer* renderer, const char* text)
{
    if(t == NULL)
    {
        log_report(ERROR, "Text: unable to create texture for a text (Text pointer is NULL) : %s", text);
        return NULL;
    }
    if(renderer == NULL)
    {
        log_report(ERROR, "Text: unable to create texture for a text (bad renderer) : %s", text);
        return NULL;
    }
    lines_texture* tex = custom_malloc(sizeof(lines_texture));
    SDL_Surface* surface = TTF_RenderUTF8_Blended(t->font, text, t->color);
    if(surface == NULL)
    {
        log_report(ERROR, "Text: unable to create surface from text : %s", text);
        custom_free(tex);
        return NULL;
    }
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(tex->texture == NULL)
    {
        log_report(ERROR, "Text: unable to create texture from surface : %s", text);
        custom_free(tex);
        return NULL;
    }
    tex->rect.x = 0;
    tex->rect.y = 0;
    SDL_QueryTexture(tex->texture, NULL, NULL, &tex->rect.w, &tex->rect.h);
    tex->next = NULL;
    return tex;
}

static int __lines_jump = 0;

void add_line(Text* t, lines_texture* line)
{
    if(line == NULL)
    {
        log_report(ERROR, "Text: unable to add a line");
        return;
    }
    lines_texture* buffer = t->texts;
    if(buffer == NULL)
    {
        t->texts = line;
        return;
    }
    while(buffer->next != NULL)
        buffer = buffer->next;
    buffer->next = line;
    buffer->rect.y += TTF_FontLineSkip(t->font) * __lines_jump;
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
        char part[len];
        while(finder != NULL)
        {
            strncpy(part, text + pos + 1, (size_t)(finder - text));
            add_line(t, generate_texture(t, renderer, part));
            pos = (int)(finder - text);
            finder = strstr(text + pos + 1, "\n");
            __lines_jump++;
        }
        strncpy(part, text + pos + 1, len - pos);
        add_line(t, generate_texture(t, renderer, part));
        __lines_jump = 0;
    }
}
void scaleText(Text* t, int x, int y, int w, int h)
{
    lines_texture* buffer = t->texts;
    while(buffer != NULL)
    {
        buffer->rect.x = x;
        buffer->rect.y = y + TTF_FontLineSkip(t->font) * __lines_jump;
        buffer->rect.w = w;
        buffer->rect.h = h;
        __lines_jump++;
        buffer = buffer->next;
    }
    __lines_jump = 0;
}
void setPosText(Text* t, int x, int y)
{
    lines_texture* buffer = t->texts;
    while(buffer != NULL)
    {
        buffer->rect.x = x;
        buffer->rect.y = y + TTF_FontLineSkip(t->font) * __lines_jump;
        __lines_jump++;
        buffer = buffer->next;
    }
    __lines_jump = 0;
}
void updateText(Text* t, SDL_Renderer* renderer, const char* text)
{
    if(t == NULL)
    {
        log_report(ERROR, "Text: unable to update a text (NULL Text pointer)");
        return;
    }
    deleteText(t);
    t->text = text;
    printf("ui\n");

    char* finder = strstr(text, "\n");
    if(finder == NULL)
        t->texts = generate_texture(t, renderer, text);
    else
    {
        int len = strlen(text);
        int pos = (int)(finder - text);
        char part[len];
        while(finder != NULL)
        {
            strncpy(part, text + pos + 1, (size_t)(finder - text));
            add_line(t, generate_texture(t, renderer, part));
            pos = (int)(finder - text);
            finder = strstr(text + pos + 1, "\n");
            __lines_jump++;
        }
        strncpy(part, text + pos + 1, len - pos);
        add_line(t, generate_texture(t, renderer, part));
        __lines_jump = 0;
    }
}
void renderText(Text* t, SDL_Renderer* renderer)
{
    lines_texture* buffer = t->texts;
    while(buffer != NULL)
    {
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
