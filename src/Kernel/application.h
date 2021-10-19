#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>
#include <IO/inputs.h>
#include <World/world.h>

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Inputs inputs;
    Floor floor;
    bool run;
} Application;

bool initApplication(Application *app);
void shutdownApplication(Application *app);
void update(Application *app);
void render(Application *app);

#endif // __APPLICATION__
