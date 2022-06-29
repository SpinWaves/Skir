// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
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
    lines_texture* tex = memAlloc(sizeof(lines_texture));
    SDL_Surface* surface = TTF_RenderUTF8_Blended(t->font, text, t->color);
    if(surface == NULL)
    {
        log_report(ERROR, "Text: unable to create surface from text : %s", text);
        memFree(tex);
        return NULL;
    }
    tex->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(tex->texture == NULL)
    {
        log_report(ERROR, "Text: unable to create texture from surface : %s", text);
        memFree(tex);
        return NULL;
    }
    tex->rect.x = t->x;
    tex->rect.y = t->y;
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

void initText(Text* t, SDL_Renderer* renderer, const char* text, SDL_Color* color, TTF_Font* font, alignment align)
{
    int len = strlen(text);
    t->align = align;
    t->text = memAlloc(sizeof(char) * len);
    t->text[len] = '\0';
    strcpy(t->text, text);
    t->font = font;
    t->color = *color;
    if(font == NULL)
        log_report(FATAL_ERROR, "Text: invalid font");

    char* finder = strchr(text, '\n');
    if(finder == NULL)
        t->texts = generate_texture(t, renderer, text);
    else
    {
        int pos = -1;
        char part[len];
        memset(part, 0, len);
        while(finder != NULL)
        {
            strncpy(part, text + pos + 1, (size_t)(finder - (text + pos) - 1));
            add_line(t, generate_texture(t, renderer, part));
            pos = (int)(finder - text);
            memset(part, 0, len);
            finder = strchr(text + pos + 1, '\n');
            __lines_jump++;
        }
        strncpy(part, text + pos + 1, len - pos);
        add_line(t, generate_texture(t, renderer, part));
        __lines_jump = 0;
    }
}

void scaleText(Text* t, int x, int y, int w, int h)
{
    t->x = x;
    t->y = y;
    lines_texture* buffer = t->texts;
    while(buffer != NULL)
    {
        switch(t->align)
        {
            case LEFT: buffer->rect.x = x; break;
            case CENTER:
                if(buffer != t->texts)
                    buffer->rect.x = x + (t->texts->rect.w - buffer->rect.w) / 2;
                else
                    buffer->rect.x = x;
                puts("test");
            break;
            case RIGHT:
                if(buffer != t->texts)
                    buffer->rect.x = x + (t->texts->rect.w - buffer->rect.w);
                else
                    buffer->rect.x = x;
            break;
        }

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
    t->x = x;
    t->y = y;
    lines_texture* buffer = t->texts;
    while(buffer != NULL)
    {
        switch(t->align)
        {
            case LEFT: buffer->rect.x = x; break;
            case CENTER:
                if(buffer != t->texts)
                    buffer->rect.x = x + (t->texts->rect.w - buffer->rect.w) / 2;
                else
                    buffer->rect.x = x;
            break;
            case RIGHT:
                if(buffer != t->texts)
                    buffer->rect.x = x + (t->texts->rect.w - buffer->rect.w);
                else
                    buffer->rect.x = x;
            break;
        }
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
    int len = strlen(text);
    t->text = memAlloc(sizeof(char) * len);
    strcpy(t->text, text);
    t->text[len] = '\0';

    char* finder = strchr(text, '\n');
    if(finder == NULL)
        t->texts = generate_texture(t, renderer, text);
    else
    {
        int pos = -1;
        char part[len];
        memset(part, 0, len);
        while(finder != NULL)
        {
            strncpy(part, text + pos + 1, (size_t)(finder - (text + pos) - 1));
            add_line(t, generate_texture(t, renderer, part));
            pos = (int)(finder - text);
            memset(part, 0, len);
            finder = strchr(text + pos + 1, '\n');
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
    memFree(t->text);
    lines_texture* buffer = t->texts;
    lines_texture* double_buffer = NULL;
    while(buffer != NULL)
    {
        double_buffer = buffer->next;
        SDL_DestroyTexture(buffer->texture);
        memFree(buffer);
        buffer = double_buffer;
    }
}
