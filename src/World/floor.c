#include <World/floor.h>
#include <Utils/c_output.h>

void initFloor(Floor* floor, SDL_Renderer* renderer, const char* text_path, unsigned int screen_w, unsigned int screen_h)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, text_path);
    if(texture == NULL)
        printf("%sFloor: unable to create texture : %s %s\n", OUT_RED, text_path, OUT_DEF);

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        x = (screen_w / 5) * i;
        y = screen_h - 30 * (screen_h / 100) + i * 10;
        w = x + screen_w/5;
        h = screen_h;
        floor->floors[i] = createSprite(renderer, texture, x, y, w, h);
    }
    floor->screen_w = screen_w;
}
void updateFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        floor->floors[i]->coords->x -= 5;
        if(floor->floors[i]->coords->x < 0)
            floor->floors[i]->coords->x = floor->screen_w;
        floor->floors[i]->coords->w = floor->floors[i]->coords->x + floor->screen_w / 5;
    }
}
void renderFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        renderSprite(floor->floors[i]);
    }
}

void shutdownFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        destroySprite(floor->floors[i]);
    }
}
