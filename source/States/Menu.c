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

    Menu* menu = (Menu*)manager->currentState.data;
    float* floorOffset = CoreFFDataGet(core, 9);
    *floorOffset = menu->floor->position.x;

    float* buildingOffset = CoreFFDataGet(core, 10);
    *buildingOffset = menu->buildings->position.x;

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
        menu->spritebatch = SpritebatchCreate(shader, 64, 2);
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
        menu->font = FontCreate("bin/resources/arial.ttf", 0, 48);
        CoreFFDataAdd(core, 7, menu->font, FontDestroy);
    }

    if(!CoreFFDataExists(core, 8)) // score
    {
        int* score = MALLOC(int);
        *score = 0;
        CoreFFDataAdd(core, 8, score, free);
        itoa(0, menu->bestScore, 10);
    }
    else
    {
        itoa(*(int*)CoreFFDataGet(core, 8), menu->bestScore, 10);
    }

    Int2 bestScoreSize = FontTextSize(menu->font, menu->bestScore, 0.5f);
    menu->bestScorePosition = (Int2){ (menu->window->size.x - bestScoreSize.x)/2, 20 };

    if(!CoreFFDataExists(core, 9)) // floor offset
    {
        float* offset = MALLOC(float);
        CoreFFDataAdd(core, 9, offset, free);
    }

    if(!CoreFFDataExists(core, 10)) // building offset
    {
        float* offset = MALLOC(float);
        CoreFFDataAdd(core, 10, offset, free);
    }

    if(!CoreFFDataExists(core, 11)) // text shader
    {
        Shader* textShader = ShaderCreate("bin/resources/spritebatch.vert", "bin/resources/spritebatchText.frag");
        CoreFFDataAdd(core, 11, textShader, ShaderDestroy);
        Mat4 pixelMat = pixelScreenMatrix(menu->window->size.x, menu->window->size.y);
        ShaderBind(textShader);
        ShaderUniformMatrixSet(textShader, "pixel", &pixelMat);
        ShaderUniformVec3Set(textShader, "TextColor", (Float3){0.0f, 0.0f, 0.0f});
    }

    if(!CoreFFDataExists(core, 12)) // text spritebatch
    {
        menu->textSpritebatch = SpritebatchCreate(CoreFFDataGet(core, 11), 64, 32);
        CoreFFDataAdd(core, 12, menu->textSpritebatch, SpritebatchDestroy);
    }
    else
    {
        menu->textSpritebatch = CoreFFDataGet(core, 12);
    }

    menu->floor = SegmentsCreate(menu->window->size.x, menu->window->size.y, CoreFFDataGet(core, 5));
    menu->buildings = SegmentsCreate(menu->window->size.x, (int)menu->floor->position.y, CoreFFDataGet(core, 6));

    WindowColorSet(0.0f, 0.0f, 1.0f, 1.0f);
    
    Int2 playTextSize = FontTextSize(menu->font, "Play", 1.0f);
    Int2 playPosition = (Int2){ (menu->window->size.x - playTextSize.x)/2, 100};
    menu->playButton = ButtonCreate(playPosition, playTextSize);
    ButtonTextSet(menu->playButton, "Play", menu->font, 1.0f);
    ButtonClickSet(menu->playButton, PlayBtn);

    Int2 quitTextSize = FontTextSize(menu->font, "Quit", 1.0f);
    Int2 quitPosition = (Int2){ (menu->window->size.x - quitTextSize.x)/2, 180};
    menu->closeButton = ButtonCreate(quitPosition, quitTextSize);
    ButtonTextSet(menu->closeButton, "Quit", menu->font, 1.0f);
    ButtonClickSet(menu->closeButton, CloseBtn);

    Int2 signatureTextSize = FontTextSize(menu->font, "Created by Aleksander Filek", 0.5f);
    menu->signaturePosition = (Int2){ menu->window->size.x - signatureTextSize.x - 5,   
        menu->window->size.y - signatureTextSize.y - 5};
}

void MenuUpdate(void* ptr, double elapsedTime)
{
    Menu* menu = (Menu*)ptr;

    SegmentsUpdate(menu->floor, elapsedTime);
    SegmentsUpdate(menu->buildings, elapsedTime);

    if(InputMouseButtonDown(menu->input, MOUSE_LEFT))
    {
        Int2 mousePosition = InputGetMousePosition(menu->input);
        ButtonUpdate(menu->playButton, mousePosition);
        ButtonUpdate(menu->closeButton, mousePosition);
    }

    WindowClear();

    SpritebatchBegin(menu->spritebatch);
    SegmentsDraw(menu->floor, menu->spritebatch);
    SegmentsDraw(menu->buildings, menu->spritebatch);
    SpritebatchEnd(menu->spritebatch);

    SpritebatchBegin(menu->textSpritebatch);
    ButtonDraw(menu->playButton, menu->textSpritebatch);
    ButtonDraw(menu->closeButton, menu->textSpritebatch);
    SpritebatchRenderText(menu->textSpritebatch, menu->font, menu->bestScore, menu->bestScorePosition, 1.0f);
    SpritebatchRenderText(menu->textSpritebatch, menu->font, "Created by Aleksander Filek", menu->signaturePosition, 0.5f);
    SpritebatchEnd(menu->textSpritebatch);

    WindowRender(menu->window);
}

void MenuDestroy(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    SegmentsDestroy(menu->floor);
}