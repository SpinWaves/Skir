#ifndef __PLAYER__
#define __PLAYER__

#include <Kernel/sprite.h>
#include <IO/inputs.h>

typedef struct
{
    Sprite* sprites[3];
    int pos_x;
    int pos_y;
    int animation_frame;
} Player;

void initPlayer(Player* player, SDL_Renderer* renderer, const char* tex[3], int x, int y);
void renderPlayer(Player* player);
void updatePlayer(Player* player, Inputs* inputs);
void shutdownPlayer(Player* player);

#endif // __PLAYER__
