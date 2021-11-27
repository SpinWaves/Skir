#include <Kernel/application.h>

#include <stdio.h>
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

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC |SDL_RENDERER_TARGETTEXTURE);
    initInput(&app->inputs);
    initFloor(&app->floor, app->renderer, MAIN_DIR"src/Assets/floor.png", WIDTH, HEIGHT);
    initFPS(&app->fps);
    initTextManager(&app->text_manager, app->renderer);
    newText(&app->text_manager, "FPS: 0", 10, 10);

    const char* player_textures[3] = {MAIN_DIR"src/Assets/player_0.png", MAIN_DIR"src/Assets/player_1.png", MAIN_DIR"src/Assets/player_2.png"};
    initPlayer(&app->player, app->renderer, player_textures, WIDTH/2, HEIGHT - WIDTH/4);

    app->run = true;

    return true;
}

void shutdownApplication(Application *app)
{
    shutdownTextManager(&app->text_manager);
    shutdownFloor(&app->floor);
    shutdownPlayer(&app->player);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}

static char* oldFPS = "FPS: 0";

void update(Application *app)
{
    updateFPS(&app->fps);
    if(app->fps.make_update)
    {
        updateInput(&app->inputs);
        if(getKey(&app->inputs, SDL_SCANCODE_ESCAPE))
            app->inputs.quit = true;

        if(app->inputs.quit)
            app->run = false;

        updateFloor(&app->floor);
        updatePlayer(&app->player, &app->inputs);
        char newFPS[12];
        sprintf(newFPS, "FPS: %d", app->fps.out_fps);
        updateText_TM(&app->text_manager, oldFPS, newFPS);
        oldFPS = newFPS;
    }
    renderPlayer(&app->player);
    renderFloor(&app->floor);
    renderTextManager(&app->text_manager);
}
