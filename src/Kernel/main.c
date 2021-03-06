// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <Kernel/kernel.h>
#include <Physics/physics.h>
#include <IO/io.h>
#include <Utils/utils.h>

#include <time.h>
#include <stdlib.h>

ColorRGB clearColor = { 141, 186, 255 };

Application app;

int main(int argc, char** argv)
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    init_logs();
    initMemManager();
    initPhysicsManager();
    initConfigInfoManager();

    default_font = TTF_OpenFont(MAIN_DIR"ressources/fonts/retro_gaming.ttf", 15);
    if(default_font == NULL)
        log_report(FATAL_ERROR, "Text Manager: cannot open default font");
    
    openConfigFile(MAIN_DIR"Languages/en.cfg");

    if(!initApplication(&app))
        log_report(FATAL_ERROR, "unable to create an application");

    while(app.run)
    {
        SDL_SetRenderDrawColor(app.renderer, clearColor.r, clearColor.g, clearColor.b, 255);
        SDL_RenderClear(app.renderer);
        
        update(&app);

        SDL_RenderPresent(app.renderer);
    }

    shutdownApplication(&app);
    destroyTextChain();
    shutdownConfigInfoManager();
    TTF_CloseFont(default_font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    shutdownPhysicsManager();
    shutdownMemManager();

    printf("%sProgram finished%s\n", OUT_BG_GREEN, OUT_BG_DEF);
    
    return 0;
}
