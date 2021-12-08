// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <Kernel/kernel.h>
#include <Physics/physics.h>

#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    initMemManager();
    initPhysicsManager();
    initConfigInfoManager();

    default_font = TTF_OpenFont(MAIN_DIR"src/fonts/OpenSans-Regular.ttf", 15);
    if(default_font == NULL)
        log_report(FATAL_ERROR, "Text Manager: cannot open default font");
    
    Application app;
    initApplication(&app);

    while(app.run)
    {
        SDL_SetRenderDrawColor(app.renderer, 90, 90, 180, 255);
        SDL_RenderClear(app.renderer);
        
        update(&app);

        SDL_RenderPresent(app.renderer);
    }

    shutdownApplication(&app);
    shutdownConfigInfoManager();
    TTF_CloseFont(default_font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    shutdownPhysicsManager();
    shutdownMemManager();
    
    return 0;
}
