// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/text_manager.h>
#include <Kernel/Memory/memory.h>
#include <Kernel/log.h>
#include <string.h>

void initTextManager(TextManager* manager, SDL_Renderer* renderer)
{
    manager->renderer = renderer;
    manager->head = NULL;
}
void newText(TextManager* manager, const char* text, int x, int y)
{
    text_link* t = (text_link*)custom_malloc(sizeof(text_link));
    SDL_Color white = { 255, 255, 255 };
    initText(&t->text, manager->renderer, text, &white, default_font);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(t->text.texts->texture, NULL, NULL, &texW, &texH);
    scaleText(&t->text, x, y, texW, texH);
    t->next = manager->head;
    manager->head = t;
}
void newText_complete(TextManager* manager, const char* text, int x, int y, int w, int h, SDL_Color* color)
{
    text_link* t = (text_link*)custom_malloc(sizeof(text_link));
    initText(&t->text, manager->renderer, text, color, default_font);
    scaleText(&t->text, x, y, w, h);
    t->next = manager->head;
    manager->head = t;
}
void passText(TextManager* manager, Text* text)
{
    text_link* t = (text_link*)custom_malloc(sizeof(text_link));
    t->text = *text;
    t->next = manager->head;
    manager->head = t;
}
void updateText_TM(TextManager* manager, const char* text_before, const char* text_update)
{
    updateText(getText(manager, text_before), manager->renderer, text_update);
}
Text* getText(TextManager* manager, const char* text)
{
    text_link* buffer = manager->head;
    while(buffer != NULL)
    {
        printf("%s, %s\n", buffer->text.text, text);
        if(strcmp(buffer->text.text, text) == 0)
            return &buffer->text;
        buffer = buffer->next;
    }
    log_report(ERROR, "Text Manager: Couldn't find the text : %s", text);
    return NULL;
}
void renderTextManager(TextManager* manager)
{
    text_link* buffer = manager->head;
    while(buffer != NULL)
    {
        renderText(&buffer->text, manager->renderer);
        buffer = buffer->next;
    }
}
void shutdownTextManager(TextManager* manager)
{
    text_link* buffer1 = manager->head;
    text_link* buffer2 = manager->head->next;
    while(buffer1 != NULL)
    {
        custom_free(buffer1);
        buffer1 = buffer2;
        if(buffer2 != NULL)
            buffer2 = buffer2->next;
    }
}
