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
    initFloor(&app->floor, app->renderer, MAIN_DIR"src/Assets/floor.png", WIDTH, HEIGHT);
    initFPS(&app->fps);
    newText(&app->text_manager, "FPS: 0", 10, 10);

    const char* player_textures[3] = {MAIN_DIR"src/Assets/player_0.png", MAIN_DIR"src/Assets/player_1.png", MAIN_DIR"src/Assets/player_2.png"};
    initPlayer(&app->player, app->renderer, player_textures, WIDTH/3, HEIGHT - WIDTH/4);

    initObstacle(&app->obs[0], app->renderer, WIDTH, MAIN_DIR"src/Assets/rock_0.png", WIDTH, HEIGHT);

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
        {
            callMainMenu();
            resetPlayer(&app->player, HEIGHT - WIDTH/4);
        }

        if(app->inputs.quit)
            app->run = false;

        if(!isMainMenuCalled())
        {
            //pm_checkCollisions();
            updateFloor(&app->floor);
            updateObstacle(&app->obs[0]);
            updatePlayer(&app->player, &app->inputs);
        }
        else
        {
            updateMainMenu(&app->inputs);
            app->obs[0].sprite->coords->x = WIDTH + 100;
            app->obs[0].hide_box->x = app->obs[0].sprite->coords->x;
            obs_can_respawn = false;
        }
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
        renderObstacle(&app->obs[0]);
        renderFloor(&app->floor);
    }
    else
        renderMainMenu();
    renderTextManager(&app->text_manager);
}

void shutdownApplication(Application *app)
{
    shutdownMainMenu();
    shutdownTextManager(&app->text_manager);
    shutdownFloor(&app->floor);
    shutdownPlayer(&app->player);
    shutdownObstacle(&app->obs[0]);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
