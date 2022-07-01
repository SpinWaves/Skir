// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/application.h>

#include <stdio.h>
#include <stdbool.h>

#include <Maths/maths.h>

#include <Utils/utils.h>

int width = 1480;
int height = 720;

bool print_fps = false;

bool initApplication(Application *app)
{
    app->window = SDL_CreateWindow("Skir", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    if(app->window == NULL)
    {
        log_report(ERROR, "Something went wrong with the creation of the window");
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED/* | SDL_RENDERER_PRESENTVSYNC*/);
    if(app->renderer == NULL)
    {
        log_report(ERROR, "Something went wrong with the creation of the renderer");
        return false;
    }

    SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);

    initTextManager(&app->text_manager, app->renderer);
    initInput(&app->inputs);
    initFPS(&app->fps);
    newText(&app->text_manager, "FPS: 0", 10, 10, LEFT);
    newText(&app->text_manager, "0 AM", width - 75, 10, LEFT);

    initPlayer(&app->player, app->renderer, width / 2, height / 2);
    initMap(&app->map, app->renderer);
    initHouse(&app->house, app->renderer, 100, 100);

    initMainMenu(app->renderer, width, height);
    callMainMenu();

    initWaterPuddle(&app->puddle, 2228, 1625, 480, 120);

    app->run = true;

    return true;
}

static char oldFPS[12] = "FPS: 0";
static char newFPS[12];

static char oldTime[5] = "0 AM";
static char newTime[5];

static bool drawHideBoxes = false;

int fading = 255;

float day_light = 0.0f;
float hours = 10.0f;

extern ColorRGB clearColor;

void update(Application* app)
{
    updateFPS(&app->fps);
    if(!isMainMenuCalled())
    {
        renderHouse(&app->house);
        renderPlayer(&app->player);
        if(!app->house.isInside)
        {
            renderWaterPuddle(&app->puddle, app->renderer);
            renderMap(&app->map);
        }
        renderHouse2(&app->house);
    }
    else
        renderMainMenu();

    renderTextManager(&app->text_manager);

    if(fading < 255)
    {
        SDL_Rect fadingRect = { 0, 0, width, height };
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, -m_abs(fading == 0 ? 1 : fading > 255 ? 255 : fading < -255 ? -255 : fading));
        SDL_RenderFillRect(app->renderer, &fadingRect);
    }

    if(app->fps.make_update)
    {
        updateInput(&app->inputs);
        if(getKey(&app->inputs, SDL_SCANCODE_ESCAPE, DOWN))
            callMainMenu();

        if(getKey(&app->inputs, SDL_SCANCODE_T, UP))
            drawHideBoxes = !drawHideBoxes;

        app->player.stopMove = fading < 255 ? true : false;

        if(app->inputs.quit)
            app->run = false;

        if(!isMainMenuCalled())
        {
            pm_checkCollisions(app->renderer, drawHideBoxes);
            updatePlayer(&app->player, &app->inputs, app->house.isInside);
            updateHouse(&app->house, &app->inputs);
            updateMap(&app->map, app->house.isInside);
            updateWaterPuddle(&app->puddle);

            hours = hours >= 24.0 ? 0.0f : hours + 0.0025;
            day_light = hours < 12.0f ? 12 * sin(0.25 * hours - 7.85) : -pow(hours, 0.048 * hours) + 0.8 * hours + 6.5;

            if(!app->house.isInside)
            {
                clearColor.r = 21 + (day_light < -2.1f ? -2.1f : day_light) * 10;
                clearColor.g = 66 + (day_light < -6.6f ? -6.6f : day_light) * 10;
                clearColor.b = 134 + (day_light < -13.4f ? -13.4f : day_light) * 10;
            }
        }
        else
            updateMainMenu(&app->inputs);
        
        if(print_fps)
            sprintf(newFPS, "FPS: %d", app->fps.out_fps);
        else
            sprintf(newFPS, " ");

        if(strcmp(oldFPS, newFPS) != 0)
        {
            updateText_TM(&app->text_manager, oldFPS, newFPS);
            strcpy(oldFPS, newFPS);
        }

        sprintf(newTime, "%d %cM", hours > 12 ? (int)(hours - 12) : (int)hours, hours > 12 ? 'P' : 'A');
        if(strcmp(oldTime, newTime) != 0)
        {
            updateText_TM(&app->text_manager, oldTime, newTime);
            strcpy(oldTime, newTime);
        }
    }
}

void shutdownApplication(Application *app)
{
    shutdownMainMenu();
    shutdownTextManager(&app->text_manager);
    shutdownPlayer(&app->player);
    destroyMap(&app->map);
    destroyHouse(&app->house);
    destroyWaterPuddle(&app->puddle);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
