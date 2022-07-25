#include"Menu.h"
#include"../Modules/Core.h"
#include"../Modules/Input.h"
#include"../Modules/Window.h"
#include"../Graphics/Shader.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Spritebatch.h"
#include"../Graphics/Font.h"
#include"../ThirdParty/GL/Gl.h"
#include"../Game/Player.h"
#include"../Game/Segments.h"
#include"../Game/Pipe.h"
#include"../UI/Button.h"
#include"../Modules/State.h"
#include"Game.h"

#include<stdio.h>
#include<stdbool.h>

extern Core* core;

EventFunction(PlayBtn)
{
    StateManager* manager = (StateManager*)CoreModuleGet(core, 3);
    StateManagerSetNext(manager, GameState);
}

EventFunction(CloseBtn)
{
    core->quit = true;
}

void MenuStart(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    menu->input = (Input*)CoreModuleGet(core, 1);
    menu->window = (Window*)CoreModuleGet(core, 2);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader* shader = NULL;

    if(!CoreFFDataExists(core, 1)) // shader
    {
        shader = ShaderCreate("bin/resources/spritebatch.vert", "bin/resources/spritebatch.frag");
        CoreFFDataAdd(core, 1, shader, ShaderDestroy);
        Mat4 pixelMat = pixelScreenMatrix(menu->window->size.x, menu->window->size.y);
        ShaderBind(shader);
        ShaderUniformMatrixSet(shader, "pixel", &pixelMat);
    }

    if(!CoreFFDataExists(core, 2)) // spritebatch
    {
        menu->spritebatch = SpritebatchCreate(shader, 64, 32);
        CoreFFDataAdd(core, 2, menu->spritebatch, SpritebatchDestroy);
    }
    else
    {
        menu->spritebatch = CoreFFDataGet(core, 2);
    }

    if(!CoreFFDataExists(core, 3)) // bird texture
    {
        Texture* texture = TextureCreate("bin/resources/Bird.png");
        CoreFFDataAdd(core, 3, texture, TextureDestroy);
    }

    if(!CoreFFDataExists(core, 4)) // pipe texture
    {
        Texture* texture = TextureCreate("bin/resources/Pipe.png");
        CoreFFDataAdd(core, 4, texture, TextureDestroy);
    }

    if(!CoreFFDataExists(core, 5)) // floor texture
    {
        Texture* texture = TextureCreate("bin/resources/Floor.png");
        CoreFFDataAdd(core, 5, texture, TextureDestroy);
    }

    if(!CoreFFDataExists(core, 6)) // buildings texture
    {
        Texture* texture = TextureCreate("bin/resources/Buildings.png");
        CoreFFDataAdd(core, 6, texture, TextureDestroy);
    }

    if(!CoreFFDataExists(core, 7)) // font
    {
        Font* font = FontCreate("bin/resources/arial.ttf", 0, 48);
        CoreFFDataAdd(core, 7, font, FontDestroy);
    }

    menu->floor = SegmentsCreate(menu->window->size.x, menu->window->size.y, CoreFFDataGet(core, 5));

    WindowColorSet(0.0f, 0.0f, 1.0f, 1.0f);
    
    Font* font = CoreFFDataGet(core, 7);

    Int2 playTextSize = FontTextSize(font, "Play", 1.0f);
    Int2 playPosition = (Int2){ (menu->window->size.x - playTextSize.x)/2, 100};
    menu->playButton = ButtonCreate(playPosition, playTextSize);
    ButtonTextSet(menu->playButton, "Play", font, 1.0f);
    ButtonClickSet(menu->playButton, PlayBtn);

    Int2 quitTextSize = FontTextSize(font, "Quit", 1.0f);
    Int2 quitPosition = (Int2){ (menu->window->size.x - quitTextSize.x)/2, 180};
    menu->closeButton = ButtonCreate(quitPosition, quitTextSize);
    ButtonTextSet(menu->closeButton, "Quit", font, 1.0f);
    ButtonClickSet(menu->closeButton, CloseBtn);
}

void MenuUpdate(void* ptr, double elapsedTime)
{
    Menu* menu = (Menu*)ptr;

    SegmentsUpdate(menu->floor, elapsedTime);

    if(InputMouseButtonDown(menu->input, MOUSE_LEFT))
    {
        Int2 mousePosition = InputGetMousePosition(menu->input);
        ButtonUpdate(menu->playButton, mousePosition);
        ButtonUpdate(menu->closeButton, mousePosition);
    }

    WindowClear();

    SpritebatchBegin(menu->spritebatch);
    SegmentsDraw(menu->floor, menu->spritebatch);
    ButtonDraw(menu->playButton, menu->spritebatch);
    ButtonDraw(menu->closeButton, menu->spritebatch);
    SpritebatchEnd(menu->spritebatch);

    WindowRender(menu->window);
}

void MenuDestroy(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    SegmentsDestroy(menu->floor);
}