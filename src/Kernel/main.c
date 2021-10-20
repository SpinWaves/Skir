#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <Kernel/kernel.h>

int main(int argc, char** argv)
{
    printf("calling path : %s\n", argv[0]);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    Application app;
    initApplication(&app);

    while(app.run)
    {
        SDL_SetRenderDrawColor(app.renderer, 0,  0, 0, 100);
        SDL_RenderClear(app.renderer);
        
        update(&app);
        render(&app);
        
        SDL_RenderPresent(app.renderer);
    }

    shutdownApplication(&app);
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
