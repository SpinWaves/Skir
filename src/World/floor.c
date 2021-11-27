#include <World/floor.h>
#include <Utils/c_output.h>
#include <SDL2/SDL_image.h>
#include <Utils/easings.h>

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
        x = (screen_w / 4) * i;
        w = screen_w / 4;
        y = screen_h - w;
        h = screen_h - y + 10;
        floor->floors[i] = createSprite(renderer, texture, x, y, w, h);
    }
    floor->screen_w = screen_w;
    floor->screen_h = screen_h;
}
static float down = 0.0f;
void updateFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        floor->floors[i]->coords->x -= 5;
        if(floor->floors[i]->coords->x < 0)
        {
            floor->floors[i]->coords->x = floor->screen_w;
            floor->floors[i]->coords->y = floor->screen_h - floor->floors[i]->coords->w;
            down = 0.0f;
        }
        if(floor->floors[i]->coords->x < floor->screen_w/5)
        {
            down += 0.15f;
            floor->floors[i]->coords->y += easeInBack(down);
        }
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
