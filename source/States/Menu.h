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
    Spritebatch* textSpritebatch;
    Font* font;

    Button* playButton;
    Button* closeButton;

    char bestScore[16];
    Int2 bestScorePosition;

    // background
    Segments* floor;
    Segments* buildings;
    Int2 signaturePosition;
} Menu;

void MenuStart(void* ptr);
void MenuUpdate(void* ptr, double elapsedTime);
void MenuDestroy(void* ptr);

#define MenuState (State){ NULL, sizeof(Menu), MenuStart, MenuUpdate, MenuDestroy }

#endif