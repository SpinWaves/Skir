#include <Kernel/application.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Utils/c_output.h>

#define WIDTH 720/2
#define HEIGHT 1280/2

bool initApplication(Application *app)
{
    app->window = SDL_CreateWindow("Keep Running", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(app->window == NULL)
    {
        printf("%sSomething went wrong with the creation of the window: %s%s\n", OUT_RED, SDL_GetError(), OUT_DEF);
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    initInput(&app->inputs);
    initFloor(&app->floor, app->renderer, NULL, WIDTH, HEIGHT);
    app->run = true;

    return true;
}

void shutdownApplication(Application *app)
{
    shutdownFloor(&app->floor);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}

void update(Application *app)
{
    updateInput(&app->inputs);
    if(getKey(&app->inputs, SDL_SCANCODE_ESCAPE))
        app->inputs.quit = true;

    if(app->inputs.quit)
        app->run = false;

    updateFloor(&app->floor);
}

void render(Application *app)
{
    renderFloor(&app->floor, app->renderer);
}
