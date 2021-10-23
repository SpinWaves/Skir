#include <World/floor.h>
#include <Utils/c_output.h>

void initFloor(Floor* floor, SDL_Renderer* renderer, const char* text_path, unsigned int screen_w, unsigned int screen_h)
{
    SDL_Surface* surf = IMG_Load(text_path);
    if(surf == NULL)
    {
        printf("%sFloor: unable to open texture image : %s : %s%s\n", OUT_RED, text_path, IMG_GetError(), OUT_DEF);
        return;
    }
    floor->texture = SDL_CreateTextureFromSurface(renderer, surf);
    if(floor->texture == NULL)
        printf("%sFloor: unable to create texture : %s %s\n", OUT_RED, text_path, OUT_DEF);
    SDL_FreeSurface(surf);

    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        floor->floors[i].x = (screen_w / 5) * i;
        floor->floors[i].y = screen_h - 30 * (screen_h / 100) + i * 10;
        floor->floors[i].w = floor->floors[i].x + screen_w/5;
        floor->floors[i].h = screen_h;
    }
    floor->screen_w = screen_w;
}
void updateFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        floor->floors[i].x -= 5;
        if(floor->floors[i].x < 0)
            floor->floors[i].x = floor->screen_w;
        floor->floors[i].w = floor->floors[i].x + floor->screen_w / 5;
    }
}
void renderFloor(Floor* floor, SDL_Renderer* renderer)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
        SDL_RenderCopy(renderer, floor->texture, NULL, &floor->floors[i]);
}

void shutdownFloor(Floor* floor)
{
    SDL_DestroyTexture(floor->texture);
}
