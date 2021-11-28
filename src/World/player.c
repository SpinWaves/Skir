#include <World/player.h>
#include <Utils/c_output.h>
#include <SDL2/SDL_image.h>

void initPlayer(Player* player, SDL_Renderer* renderer, const char* tex[3], int x, int y)
{
    SDL_Texture* texture = NULL;
    int w, h = 0;
    player->animation_frame = 0;
    for(int i = 0; i < sizeof(player->sprites)/sizeof(player->sprites[0]); i++)
    {
        texture = IMG_LoadTexture(renderer, tex[i]);
        if(texture == NULL)
            printf("%sPlayer: unable to create texture : %s %s\n", OUT_RED, tex[i], OUT_DEF);
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        if(i % 2 == 0)
            y += 4;
        else
            y -= 8;
        player->sprites[i] = createSprite(renderer, texture, x - w/2, y - h, w, h);
    }
    player->hide_box = newBoxCollider(x, y, player->sprites[0]->coords->w, player->sprites[0]->coords->h);
}
void renderPlayer(Player* player)
{
    renderSprite(player->sprites[(int)(player->animation_frame/100)]);
}
static int jump = -14;
void updatePlayer(Player* player, Inputs* inputs)
{
    player->hide_box->y = player->sprites[(int)(player->animation_frame/100)]->coords->y;
    if(jump == -14)
    {
        if(getKey(inputs, SDL_SCANCODE_SPACE) || getKey(inputs, SDL_SCANCODE_UP))
            jump = 15;

        player->animation_frame += 15;
        if(player->animation_frame >= 300)
            player->animation_frame = 0;
    }
    else
    {
        jump--;
        player->sprites[(int)(player->animation_frame/100)]->coords->y -= jump;
    }
}
void shutdownPlayer(Player* player)
{
    freeBoxCollider(player->hide_box);
    for(int i = 0; i < sizeof(player->sprites)/sizeof(player->sprites[0]); i++)
    {
        destroySprite(player->sprites[i]);
    }
}
