// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <World/player.h>
#include <Utils/utils.h>
#include <SDL2/SDL_image.h>
#include <Physics/physics.h>
#include <GUI/main_menu.h>
#include <Kernel/log.h>
#include <Maths/maths.h>

float mov_x;
float mov_y;

void initPlayer(Player* player, SDL_Renderer* renderer, int x, int y)
{
    SDL_Texture* texture = NULL;
    int w, h = 0;
    player->animation_frame = 0;

    mov_x = -500;
    mov_y = -700;
    
    const char* player_idle_textures[3] = {
        MAIN_DIR"ressources/Assets/player/player_idle_0.png",
        MAIN_DIR"ressources/Assets/player/player_idle_1.png",
        MAIN_DIR"ressources/Assets/player/player_idle_2.png"
    };

    for(int i = 0; i < ARRAY_SIZE(player->idle_sprites); i++)
    {
        texture = IMG_LoadTexture(renderer, player_idle_textures[i]);
        if(texture == NULL)
            log_report(ERROR, "Player : unable to create texture : %s", player_idle_textures[i]);
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        player->idle_sprites[i] = createSprite(renderer, texture, x - w / 2, y - h, w * 2, h * 2);
    }

    const char* player_running_textures[6] = {
        MAIN_DIR"ressources/Assets/player/player_running_0.png",
        MAIN_DIR"ressources/Assets/player/player_running_1.png",
        MAIN_DIR"ressources/Assets/player/player_running_2.png",
        MAIN_DIR"ressources/Assets/player/player_running_3.png",
        MAIN_DIR"ressources/Assets/player/player_running_4.png",
        MAIN_DIR"ressources/Assets/player/player_running_5.png",
    };

    for(int i = 0; i < ARRAY_SIZE(player->running_sprites); i++)
    {
        texture = IMG_LoadTexture(renderer, player_running_textures[i]);
        if(texture == NULL)
            log_report(ERROR, "Player : unable to create texture : %s", player_running_textures[i]);
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        player->running_sprites[i] = createSprite(renderer, texture, x - w / 2, y - h, w * 2, h * 2);
    }

    player->hide_box = newBoxCollider(player->idle_sprites[0]->coords->x + 7, player->idle_sprites[0]->coords->y, player->idle_sprites[0]->coords->w - 7, player->idle_sprites[0]->coords->h - 12, true);
    pm_addCollider(player->hide_box);
}

static bool is_running = false;

void renderPlayer(Player* player)
{
    if(is_running)
        renderRotateSprite(player->running_sprites[(int)(player->animation_frame / 100)]);
    else
        renderRotateSprite(player->idle_sprites[(int)((player->animation_frame > 300 ? 300 : player->animation_frame) / 100)]);
}

static float gravity = 0.0f;
static bool noclip = false;

void updatePlayer(Player* player, Inputs* inputs)
{
    if(!player->hide_box->bottom_collision && !noclip)
    {
        gravity += 0.2f;
        gravity *= 1.01f;
    }
    else
        gravity = 0.0f;

    if(getKey(inputs, SDL_SCANCODE_N, UP))
        noclip = !noclip;

    if(getKey(inputs, SDL_SCANCODE_SPACE, DOWN))
    {
        if(noclip)
            gravity = -7;
        else if(player->hide_box->bottom_collision)// && !player->hide_box->top_collision)
        {
            mov_y += 5;
            gravity -= 5;
        }
    }

    if((getKey(inputs, SDL_SCANCODE_LSHIFT, DOWN) || getKey(inputs, SDL_SCANCODE_RSHIFT, DOWN)) && noclip)
        gravity = 7;

    if(is_running)
    {
        player->animation_frame += 15;
        if(player->animation_frame >= 600)
            player->animation_frame = 0;
    }
    else
    {
        player->animation_frame += 7;
        if(player->animation_frame >= 300)
            player->animation_frame = 0;
    }

    is_running = false;

    if(getKey(inputs, SDL_SCANCODE_LEFT, DOWN) || getKey(inputs, SDL_SCANCODE_A, DOWN))
    {
        is_running = true;
        player->running_sprites[(int)(player->animation_frame / 100)]->flip_horizontal = false;

        if(player->idle_sprites[0]->flip_horizontal == true)
        {
            for(int i = 0; i < ARRAY_SIZE(player->idle_sprites); i++)
                player->idle_sprites[i]->flip_horizontal = false;
        }

        if(noclip || !player->hide_box->left_collision)
            mov_x += 7;
    }

    if(getKey(inputs, SDL_SCANCODE_RIGHT, DOWN) || getKey(inputs, SDL_SCANCODE_D, DOWN))
    {
        is_running = !is_running;
        player->running_sprites[(int)(player->animation_frame / 100)]->flip_horizontal = true;

        if(player->idle_sprites[0]->flip_horizontal == false)
        {
            for(int i = 0; i < ARRAY_SIZE(player->idle_sprites); i++)
                player->idle_sprites[i]->flip_horizontal = true;
        }

        if(noclip || !player->hide_box->right_collision)
            mov_x -= 7;
    }

    mov_y -= gravity;

    if(player->hide_box->bottom_collision)
    {
        int hide_box_y_save = player->hide_box->y;
        while(player->hide_box->bottom_collision)
        {
            mov_y++;
            player->hide_box->y--;
            pm_checkCollisionsCollider(player->hide_box);
        }
        mov_y--;
        player->hide_box->y = hide_box_y_save;
    }
}

void shutdownPlayer(Player* player)
{
    freeBoxCollider(player->hide_box);
    for(int i = 0; i < ARRAY_SIZE(player->idle_sprites); i++)
        destroySprite(player->idle_sprites[i]);

    for(int i = 0; i < ARRAY_SIZE(player->running_sprites); i++)
        destroySprite(player->running_sprites[i]);
}
