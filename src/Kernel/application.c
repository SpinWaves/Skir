#include <Kernel/application.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Utils/c_output.h>

bool initApplication(Application *app)
{
    app->window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720/2, 1280/2, SDL_WINDOW_ALLOW_HIGHDPI);
    if(app->window == NULL)
    {
        printf("%sSomething went wrong with the creation of the window: %s%s\n", OUT_RED, SDL_GetError(), OUT_DEF);
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    app->inputs = (Inputs*)custom_malloc(sizeof(Inputs));
    app->inputs->quit = false;
    initInput(app->inputs);
    app->run = true;

    return true;
}

void shutdownApplication(Application *app)
{
    custom_free(app->inputs);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    app->window = NULL;
}

void update(Application *app)
{
    updateInput(app->inputs);
    if(getKey(app->inputs, SDL_SCANCODE_ESCAPE))
        app->inputs->quit = true;

    if(app->inputs->quit)
        app->run = false;
}
