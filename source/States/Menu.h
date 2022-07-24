#ifndef TB_MENU_H_
#define TB_MENU_H_

#include"../Defaults.h"

STRUCT(Window);
STRUCT(Input);
STRUCT(Spritebatch);
STRUCT(Segments);
STRUCT(Button);

typedef struct Menu
{
    // basic
    Window* window;
    Input* input;
    Spritebatch* spritebatch;

    Button* closeButton;

    // background
    Segments* floor;
} Menu;

void MenuStart(void* ptr);
void MenuUpdate(void* ptr, double elapsedTime);
void MenuDestroy(void* ptr);

#define MenuState (State){ NULL, sizeof(Menu), MenuStart, MenuUpdate, MenuDestroy }

#endif