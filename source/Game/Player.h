#ifndef PLAYER_H_
#define PLATER_H_

#include"../Defaults.h"
#include"../Physics.h"

#include<stdbool.h>

#define GRAVITY -9.81f
#define ACCELERATIONLIMIT -8.0f
#define RADIUS 5
#define JUMPVELOCITY 4

STRUCT(Input);
STRUCT(Texture);
STRUCT(Spritebatch);

typedef struct Player
{
    Input* input;
    Texture* texture;

    CircleCollision2D collider;

    bool alive;
    Float2 position;
    Int2 globalPosition;
    float velocity;
} Player;

Player* PlayerCreate(Input* input, Int2 startPosition);
void PlayerDestroy(Player* player);
void PlayerDie(Player* player);
void PlayerUpdate(Player* player, double elapsedTime);
void PlayerDraw(Player* player, Spritebatch* spritebatch);

#endif