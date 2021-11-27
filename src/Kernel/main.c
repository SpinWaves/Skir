#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <Kernel/kernel.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    initMemManager();
    
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
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    shutdownMemManager();
    
    return 0;
}
