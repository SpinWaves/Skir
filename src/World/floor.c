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
        floor->downs[i] = 0.0f;
        x = (screen_w / 4) * i;
        w = screen_w / 4;
        y = screen_h - w;
        h = screen_h - y + 10;
        floor->floors[i] = createSprite(renderer, texture, x, y, w, h);
        floor->floors[i]->angle = 0;
    }
    floor->screen_w = screen_w;
    floor->screen_h = screen_h;
}
void updateFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        floor->floors[i]->coords->x -= 5;
        if(floor->floors[i]->coords->x <= -floor->floors[i]->coords->w)
        {
            floor->floors[i]->coords->x = floor->screen_w;
            floor->floors[i]->coords->y = floor->screen_h - floor->floors[i]->coords->w;
            floor->downs[i] = 0.0f;
            floor->floors[i]->angle = 0;
        }
        if(floor->floors[i]->coords->x < (int)(floor->screen_w/10) && floor->floors[i]->coords->y < (int)floor->screen_h)
        {
            floor->downs[i] += 0.1f;
            floor->floors[i]->coords->y += easeInBack(floor->downs[i]);
            floor->floors[i]->angle--;
        }
    }
}
void renderFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        renderRotateSprite(floor->floors[i]);
    }
}

void shutdownFloor(Floor* floor)
{
    for(int i = 0; i < sizeof(floor->floors)/sizeof(floor->floors[0]); i++)
    {
        destroySprite(floor->floors[i]);
    }
}
