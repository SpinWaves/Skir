#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>
#include <IO/inputs.h>
#include <World/world.h>
#include <Utils/fps.h>
#include <Kernel/text_manager.h>
#include <Physics/physics.h>

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Inputs inputs;
    Floor floor;
    FPS_counter fps;
    TextManager text_manager;
    Player player;
    Obstacle obs[2];
    bool run;
} Application;

bool initApplication(Application *app);
void shutdownApplication(Application *app);
void update(Application *app);

#endif // __APPLICATION__
