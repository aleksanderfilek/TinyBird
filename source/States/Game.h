#ifndef GAME_H_
#define GAME_H_

#include"../Defaults.h"
#include"../Modules/State.h"
#include"../Math.h"

STRUCT(Window);
STRUCT(Mesh);
STRUCT(Texture);
STRUCT(Spritebatch);
STRUCT(Player);
STRUCT(Segments);
STRUCT(PipeManager);

typedef struct Game
{
    Window* window;
    Spritebatch* spritebatch;

    Player* player;
    Segments* floor;
    Segments* buildings;
    PipeManager* pipeManager;
} Game;

void GameStart(void* ptr);
void GameUpdate(void* ptr, double elapsedTime);
void GameDestroy(void* ptr);

#define GameState (State){ NULL, sizeof(Game), GameStart, GameUpdate, GameDestroy }


#endif