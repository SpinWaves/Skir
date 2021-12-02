#include <Kernel/application.h>

#include <stdio.h>
#include <stdbool.h>

#include <Utils/c_output.h>

#define WIDTH (720/2)
#define HEIGHT (1280/2)

void button_do()
{
    printf("test\n");
}

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
    initPlayer(&app->player, app->renderer, player_textures, WIDTH/3, HEIGHT - WIDTH/4);

    initObstacle(&app->obs[0], app->renderer, WIDTH, MAIN_DIR"src/Assets/rock_0.png", WIDTH, HEIGHT);

    app->but = createButton(app->renderer, "Test", 100, 200, 100, 50, 255, 255, 255);
    setFunctionCall(app->but, button_do);

    app->run = true;

    return true;
}

static char* oldFPS = "FPS: 0";

void update(Application *app)
{
    updateFPS(&app->fps);
    if(app->fps.make_update)
    {
        updateInput(&app->inputs);
        if(getKey(&app->inputs, SDL_SCANCODE_ESCAPE, DOWN))
            app->inputs.quit = true;

        if(app->inputs.quit)
            app->run = false;

        updateFloor(&app->floor);
        updateObstacle(&app->obs[0]);
        updatePlayer(&app->player, &app->inputs);
        updateButton(app->but, &app->inputs);

        pm_checkCollisions();

        char newFPS[12];
        sprintf(newFPS, "FPS: %d", app->fps.out_fps);
        updateText_TM(&app->text_manager, oldFPS, newFPS);
        oldFPS = newFPS;
    }
    renderButton(app->but);
    renderPlayer(&app->player);
    renderObstacle(&app->obs[0]);
    renderFloor(&app->floor);
    renderTextManager(&app->text_manager);
}

void shutdownApplication(Application *app)
{
    destroyButton(app->but);
    shutdownTextManager(&app->text_manager);
    shutdownFloor(&app->floor);
    shutdownPlayer(&app->player);
    shutdownObstacle(&app->obs[0]);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
