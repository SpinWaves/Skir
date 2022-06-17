// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/application.h>

#include <stdio.h>
#include <stdbool.h>

#include <Utils/c_output.h>

bool initApplication(Application *app)
{
    app->window = SDL_CreateWindow("Keep Running", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(app->window == NULL)
    {
        log_report(ERROR, "Something went wrong with the creation of the window");
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(app->renderer == NULL)
    {
        log_report(ERROR, "Something went wrong with the creation of the renderer");
        return false;
    }

    initTextManager(&app->text_manager, app->renderer);
    initInput(&app->inputs);
    initFPS(&app->fps);
    newText(&app->text_manager, "FPS: 0", 10, 10);

    initPlayer(&app->player, app->renderer, WIDTH / 2, HEIGHT / 2);

    initMap(&app->map, app->renderer);

    initMainMenu(app->renderer, WIDTH, HEIGHT);
    callMainMenu();

    app->run = true;

    return true;
}

static char oldFPS[12] = "FPS: 0";
static char newFPS[12];

void update(Application *app)
{
    updateFPS(&app->fps);
    if(app->fps.make_update)
    {
        updateInput(&app->inputs);
        if(getKey(&app->inputs, SDL_SCANCODE_ESCAPE, DOWN))
            callMainMenu();

        if(app->inputs.quit)
            app->run = false;

        if(!isMainMenuCalled())
        {
            pm_checkCollisions();
            updatePlayer(&app->player, &app->inputs);
        }
        else
            updateMainMenu(&app->inputs);
        sprintf(newFPS, "FPS: %d", app->fps.out_fps);
        if(strcmp(oldFPS, newFPS) != 0)
        {
            updateText_TM(&app->text_manager, oldFPS, newFPS);
            strcpy(oldFPS, newFPS);
        }
    }
    if(!isMainMenuCalled())
    {
        renderPlayer(&app->player);
        renderMap(&app->map);
    }
    else
        renderMainMenu();
    renderTextManager(&app->text_manager);
}

void shutdownApplication(Application *app)
{
    shutdownMainMenu();
    shutdownTextManager(&app->text_manager);
    shutdownPlayer(&app->player);
    destroyMap(&app->map);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
