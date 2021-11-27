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
            printf("%sFloor: unable to create texture : %s %s\n", OUT_RED, tex[i], OUT_DEF);
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        if(i == 1)
            y += 3;
        if(i == 2)
            y -= 6;
        if(i == 3)
            y += 3;
        player->sprites[i] = createSprite(renderer, texture, x - w/2, y - h, w, h);
    }
}
void renderPlayer(Player* player)
{
    renderSprite(player->sprites[(int)(player->animation_frame/100)]);
}
void updatePlayer(Player* player)
{
    player->animation_frame += 15;
    if(player->animation_frame >= 300)
        player->animation_frame = 0;
}
void shutdownPlayer(Player* player)
{
    for(int i = 0; i < sizeof(player->sprites)/sizeof(player->sprites[0]); i++)
    {
        destroySprite(player->sprites[i]);
    }
}
