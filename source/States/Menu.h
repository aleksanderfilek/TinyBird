#ifndef TB_MENU_H_
#define TB_MENU_H_

#include"../Defaults.h"
#include"../Modules/State.h"
#include<stdint.h>
#include"../Math.h"

STRUCT(Window);
STRUCT(Mesh);
STRUCT(Texture);
STRUCT(Spritebatch);
STRUCT(Player);
STRUCT(Segments);
STRUCT(PipeManager);

typedef struct Menu
{
    Window* window;
    Spritebatch* spritebatch;

    Player* player;
    Segments* floor;
    Segments* buildings;
    PipeManager* pipeManager;
} Menu;

void MenuStart(void* ptr);
void MenuUpdate(void* ptr, double elapsedTime);
void MenuDestroy(void* ptr);

#define MenuState (State){ NULL, sizeof(Menu), MenuStart, MenuUpdate, MenuDestroy }

#endif