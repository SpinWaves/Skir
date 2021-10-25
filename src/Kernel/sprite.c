#include <Kernel/sprite.h>
#include <Kernel/Memory/memory.h>

Sprite* createSprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
    Sprite* sprite = custom_malloc(sizeof(Sprite));
    sprite->texture = texture;
    sprite->renderer = renderer;
    sprite->coords = custom_malloc(sizeof(SDL_Rect));
    sprite->coords->x = x;
    sprite->coords->y = y;
    sprite->coords->w = w;
    sprite->coords->h = h;
    return sprite;
}
void setCoords(Sprite *sprite, int x, int y, int w, int h)
{
    sprite->coords->x = x;
    sprite->coords->y = y;
    sprite->coords->w = w;
    sprite->coords->h = h;
}
void renderSprite(Sprite* sprite)
{
    SDL_RenderCopy(sprite->renderer, sprite->texture, NULL, sprite->coords);
}
void destroySprite(Sprite* sprite)
{
    SDL_DestroyTexture(sprite->texture);
    custom_free(sprite->coords);
    custom_free(sprite);
}
