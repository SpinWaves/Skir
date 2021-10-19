#ifndef __FLOOR__
#define __FLOOR__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
    SDL_Rect floors[5];
    unsigned int speed;
    SDL_Texture* texture;
} Floor;

void initFloor(Floor* floor, SDL_Renderer* renderer, const char* text_path, unsigned int screen_w, unsigned int screen_h);
void updateFloor(Floor* floor);
void renderFloor(Floor* floor, SDL_Renderer* renderer);
void shutdownFloor(Floor* floor);

#endif // __FLOOR__ 
