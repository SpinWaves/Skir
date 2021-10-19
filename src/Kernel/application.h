#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>
#include <IO/inputs.h>

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Inputs inputs;
    bool run;
} Application;

bool initApplication(Application *app);
void shutdownApplication(Application *app);
void update(Application *app);

#endif // __APPLICATION__
