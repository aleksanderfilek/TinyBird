#ifndef TB_MENU_H_
#define TB_MENU_H_

#include"../Defaults.h"
#include"../Math.h"

STRUCT(Window);
STRUCT(Input);
STRUCT(Spritebatch);
STRUCT(Segments);
STRUCT(Button);
STRUCT(Font);

typedef struct Menu
{
    // basic
    Window* window;
    Input* input;
    Spritebatch* spritebatch;
    Font* font;

    Button* playButton;
    Button* closeButton;

    // background
    Segments* floor;
    Int2 signaturePosition;
} Menu;

void MenuStart(void* ptr);
void MenuUpdate(void* ptr, double elapsedTime);
void MenuDestroy(void* ptr);

#define MenuState (State){ NULL, sizeof(Menu), MenuStart, MenuUpdate, MenuDestroy }

#endif