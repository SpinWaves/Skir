#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <Kernel/kernel.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    Application app;
    initApplication(&app);

    while(app.run)
    {
        update(&app);
        SDL_RenderClear(app.renderer);
        SDL_RenderPresent(app.renderer);
    }

    shutdownApplication(&app);
    SDL_Quit();
    shutdownMemManager();
    
    return 0;
}
