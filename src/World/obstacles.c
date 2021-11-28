#include <World/obstacles.h>
#include <Utils/utils.h>
#include <SDL2/SDL_image.h>
#include <Utils/easings.h>

void initObstacle(Obstacle* obstacle, SDL_Renderer * renderer, int x, const char* tex, unsigned int screen_w, unsigned int screen_h)
{
    int w, h = 0;
    obstacle->down = 0.0f;
    obstacle->wiggle = 0;
    obstacle->screen_w = screen_w;
    obstacle->screen_h = screen_h;
    SDL_Texture* texture = IMG_LoadTexture(renderer, tex);
    if(texture == NULL)
        printf("%sObstacle: unable to create texture : %s %s\n", OUT_RED, tex, OUT_DEF);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    obstacle->sprite = createSprite(renderer, texture, x, screen_h - screen_w/4 - h + 10, w, h);
    obstacle->hide_box = newBoxCollider(x, screen_h - screen_w/4 - h + 10, w, h);
}
void renderObstacle(Obstacle* obstacle)
{
    renderRotateSprite(obstacle->sprite);
}
void updateObstacle(Obstacle* obstacle)
{
    obstacle->sprite->coords->x -= 5;
    obstacle->hide_box->x = obstacle->sprite->coords->x;
    if(obstacle->sprite->coords->x <= -obstacle->sprite->coords->w)
    {
        obstacle->sprite->coords->x = obstacle->screen_w;
        obstacle->sprite->coords->y = obstacle->screen_h - obstacle->screen_w/4 - obstacle->sprite->coords->h + 10;
        obstacle->down = 0.0f;
        obstacle->wiggle = 0;
        obstacle->sprite->angle = 0;
    }
    if(obstacle->sprite->coords->x < (int)(obstacle->screen_w/20) && obstacle->sprite->coords->y < obstacle->screen_h)
    {
        obstacle->down += 0.1f;
        obstacle->sprite->coords->y += easeInBack(obstacle->down);
        obstacle->sprite->angle--;
    }
    else if(obstacle->sprite->coords->x < (int)(obstacle->screen_w/4))
    {
        obstacle->sprite->angle = cos(obstacle->wiggle) * 4;
        obstacle->wiggle++;
    }
}
void shutdownObstacle(Obstacle* obstacle)
{
    destroySprite(obstacle->sprite);
}
