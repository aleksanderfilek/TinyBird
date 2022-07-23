#include"Player.h"
#include"../Modules/Input.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Spritebatch.h"

#include<stdlib.h>
#include<stdio.h>

Player* PlayerCreate(Input* input, Int2 startPosition)
{
    Player* player = (Player*)malloc(sizeof(Player));

    player->input = input;
    player->alive = true;
    player->position = (Float2){ startPosition.x, startPosition.y };
    player->velocity = 0.0f;

    player->texture = TextureCreate("bin/resources/Bird.png");

    player->collider.position = startPosition;
    player->collider.radius = RADIUS;

    return player;
}

void PlayerDestroy(Player* player)
{
    TextureDestroy(player->texture);
    free(player);
}

void PlayerDie(Player* player)
{
    player->alive = false;
}

void PlayerUpdate(Player* player, double elapsedTime)
{
    if(!player->alive)
    {
        return;
    }

    if(InputKeyDown(player->input, KEYCODE_SPACE))
    {
        player->velocity = JUMPVELOCITY;
    }

    player->velocity += GRAVITY * elapsedTime;
    if(player->velocity < ACCELERATIONLIMIT)
    {
        player->velocity = ACCELERATIONLIMIT;
    }

    player->position.y -= player->velocity;
    
    player->collider.position = Float2ToInt2(player->position);
}

void PlayerDraw(Player* player, Spritebatch* spritebatch)
{
    Int2 position = (Int2){ (int)player->position.x - 18, (int)player->position.y + 18 };

    float zRect = (player->velocity <= 0)? 0.0f : 0.5f;

    SpritebatchDraw(spritebatch, player->texture, position, (Int2){36, 36}, (Float4){zRect, 0.0f, zRect + 0.5f, 1.0f});
}