// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <GUI/button.h>
#include <Kernel/Memory/memory.h>
#include <Kernel/text_manager.h>
#include <Kernel/log.h>

Button* createButton(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h, int r, int g, int b, int font_size, bool is_key)
{
    Button* button = memAlloc(sizeof(Button));
    button->coords = memAlloc(sizeof(SDL_Rect));
    button->coords->x = x;
    button->coords->y = y;
    button->coords->w = w;
    button->coords->h = h;

    button->color = memAlloc(sizeof(SDL_Color));
    button->color->r = r;
    button->color->g = g;
    button->color->b = b;
    button->color->a = 255;

    button->renderer = renderer;
    button->f = NULL;
    button->is_activated = false;
    button->trigger = false;
    button->is_released = false;

    button->font = TTF_OpenFont(MAIN_DIR"ressources/fonts/retro_gaming.ttf", font_size);
    if(button->font == NULL)
        log_report(FATAL_ERROR, "Button : cannot open font");
    SDL_Color white = { 255, 255, 255, 255 };
    button->text = memAlloc(sizeof(Text));
    if(is_key)
        initTextKey(button->text, button->renderer, text, &white, button->font, LEFT);
    else
        initText(button->text, button->renderer, text, &white, button->font, LEFT);

    int rect_text_x = button->coords->x + (button->coords->w - button->text->texts->rect.w)/2;
    int rect_text_y = button->coords->y + (button->coords->h - button->text->texts->rect.h)/2 + 1;
    scaleText(button->text, rect_text_x, rect_text_y, button->text->texts->rect.w, button->text->texts->rect.h);

    button->sprite = NULL;

    return button;
}

Button* createButtonTextured(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h, Sprite* sprite, int font_size, bool is_key)
{
    Button* button = memAlloc(sizeof(Button));
    button->coords = memAlloc(sizeof(SDL_Rect));
    button->coords->x = x;
    button->coords->y = y;
    button->coords->w = w;
    button->coords->h = h;

    button->color = NULL;

    button->renderer = renderer;
    button->f = NULL;
    button->is_activated = false;
    button->trigger = false;
    button->is_released = false;

    button->font = TTF_OpenFont(MAIN_DIR"ressources/fonts/retro_gaming.ttf", font_size);
    if(button->font == NULL)
        log_report(FATAL_ERROR, "Button : cannot open font");
    SDL_Color white = { 255, 255, 255, 255 };
    button->text = memAlloc(sizeof(Text));
    if(is_key)
        initTextKey(button->text, button->renderer, text, &white, button->font, LEFT);
    else
        initText(button->text, button->renderer, text, &white, button->font, LEFT);

    int rect_text_x = button->coords->x + (button->coords->w - button->text->texts->rect.w)/2;
    int rect_text_y = button->coords->y + (button->coords->h - button->text->texts->rect.h)/2 + 1;
    scaleText(button->text, rect_text_x, rect_text_y, button->text->texts->rect.w, button->text->texts->rect.h);

    button->sprite = sprite;
    button->sprite->day_night_cycle = false;
    button->sprite->coords->x = x;
    button->sprite->coords->y = y;
    button->sprite->coords->w = w;
    button->sprite->coords->h = h;

    return button;
}

inline void setFunctionCall(Button* button, void (*f)())
{
    button->f = f;
}

inline bool isDown(Button* button)
{
    return button->is_activated;
}

void renderButton(Button* button)
{
    if(!button->trigger)
    {
        if(button->color != NULL)
        {
            SDL_SetRenderDrawColor(button->renderer, button->color->r, button->color->g, button->color->b, 255);
            SDL_RenderFillRect(button->renderer, button->coords);
        }
        else if(button->sprite != NULL)
        {
            SDL_SetTextureColorMod(button->sprite->texture, 230, 210, 220);
            renderRotateSprite(button->sprite);
        }
    }
    else
    {
        if(button->color != NULL)
        {
            SDL_SetRenderDrawColor(button->renderer, button->color->r + 15, button->color->g + 15, button->color->b + 15, 255);
            SDL_RenderFillRect(button->renderer, button->coords);
        }
        else if(button->sprite != NULL)
        {
            SDL_SetTextureColorMod(button->sprite->texture, 255, 255, 255);
            renderRotateSprite(button->sprite);
        }
    }
    if(button->is_activated)
    {
        if(button->color != NULL)
        {
            SDL_SetRenderDrawColor(button->renderer, button->color->r - 40, button->color->g - 40, button->color->b - 40, 255);
            SDL_RenderFillRect(button->renderer, button->coords);
        }
        else if(button->sprite != NULL)
        {
            SDL_SetTextureColorMod(button->sprite->texture, 160, 140, 150);
            renderRotateSprite(button->sprite);
        }
    }
    renderText(button->text, button->renderer);
}

void updateButton(Button* button, Inputs* inputs)
{
    button->is_released = false;
    if (   getMouseY(inputs) > button->coords->y
        && getMouseY(inputs) <= button->coords->y + button->coords->h
        && getMouseX(inputs) > button->coords->x
        && getMouseX(inputs) <= button->coords->x + button->coords->w
        && getMouse(inputs, 1, DOWN))
    {
        button->is_activated = true;
        button->trigger = true;
    }

    if(getMouse(inputs, 1, UP))
    {
        if(button->is_activated && button->f != NULL)
            button->f();
        button->is_released = button->is_activated;
        button->is_activated = false;
    }

    if (   getMouseY(inputs) > button->coords->y
        && getMouseY(inputs) <= button->coords->y + button->coords->h
        && getMouseX(inputs) > button->coords->x
        && getMouseX(inputs) <= button->coords->x + button->coords->w)
        button->trigger = true;
    else
       button->trigger = false;
}

void destroyButton(Button* button)
{
    deleteText(button->text);
    if(button->sprite != NULL)
        destroySprite(button->sprite);

    TTF_CloseFont(button->font);

    memFree(button->text);
    if(button->color != NULL)
        memFree(button->color);
    memFree(button->coords);
    memFree(button);
}
