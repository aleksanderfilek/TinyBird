#ifndef TB_MENU_H_
#define TB_MENU_H_

#include"../Defaults.h"
#include"../Modules/State.h"
#include<stdint.h>
#include"../Math.h"

STRUCT(Input);
STRUCT(Window);
STRUCT(Shader);
STRUCT(Mesh);
STRUCT(Texture);
STRUCT(Spritebatch);
STRUCT(RenderTarget);
STRUCT(Font);

typedef struct Menu
{
    Input* input;
    Window* window;
    Shader* shader;
    Texture* texture;
    Mesh* mesh;
    Spritebatch* spritebatch;
    Shader* simpleShader;
    RenderTarget* renderTarget;
    Font* font;
    Mat4 pixelMat;
    Mat4 smallPixelMat;
} Menu;

void MenuStart(void* ptr);
void MenuUpdate(void* ptr, double elapsedTime);
void MenuDestroy(void* ptr);

#define MenuState (State){ NULL, sizeof(Menu), MenuStart, MenuUpdate, MenuDestroy }

#endif