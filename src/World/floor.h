#ifndef __FLOOR__
#define __FLOOR__

#include <SDL2/SDL.h>
#include <Kernel/sprite.h>

typedef struct
{
    Sprite* floors[5];
    float downs[5];
    unsigned int speed;
    unsigned int screen_w;
    unsigned int screen_h;
} Floor;

void initFloor(Floor* floor, SDL_Renderer* renderer, const char* text_path, unsigned int screen_w, unsigned int screen_h);
void updateFloor(Floor* floor);
void renderFloor(Floor* floor);
void shutdownFloor(Floor* floor);

#endif // __FLOOR__ 
