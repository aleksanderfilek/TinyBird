#include"Menu.h"
#include"../Modules/Core.h"
#include"../Modules/Input.h"
#include"../Modules/Window.h"
#include"../Graphics/Shader.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Spritebatch.h"
#include"../ThirdParty/GL/Gl.h"
#include"../Game/Player.h"
#include"../Game/Segments.h"
#include"../Game/Pipe.h"

#include<stdio.h>
#include<stdbool.h>

extern Core* core;

void MenuStart(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    menu->window = (Window*)CoreModuleGet(core, 2);

    menu->player = PlayerCreate((Input*)CoreModuleGet(core, 1), 
        (Int2){ menu->window->size.x/3, menu->window->size.y/2 });

    Shader* shader = ShaderCreate("bin/resources/spritebatch.vert", "bin/resources/spritebatch.frag");
    CoreFFDataAdd(core, 0, shader, ShaderDestroy);
    Mat4 pixelMat = pixelScreenMatrix(menu->window->size.x, menu->window->size.y);
    ShaderBind(shader);
    ShaderUniformMatrixSet(shader, "pixel", &pixelMat);

    menu->spritebatch = SpritebatchCreate(shader, 10, 32);
    CoreFFDataAdd(core, 1, shader, ShaderDestroy);

    WindowColorSet(0.0f, 0.0f, 1.0f, 1.0f);

    menu->floor = SegmentsCreate(menu->window->size.x, menu->window->size.y, "bin/resources/Floor.png");
    menu->buildings = SegmentsCreate(menu->window->size.x, (int)menu->floor->position.y, "bin/resources/Buildings.png");
    menu->pipeManager = PipeManagerCreate((Int2){0,0}, 3, menu->window->size.x, menu->buildings->position.y);
}

void MenuUpdate(void* ptr, double elapsedTime)
{
    Menu* menu = (Menu*)ptr;

    PlayerUpdate(menu->player, elapsedTime);
    SegmentsUpdate(menu->floor, elapsedTime);
    SegmentsUpdate(menu->buildings, elapsedTime);
    PipeManagerUpdate(menu->pipeManager, elapsedTime);

    WindowClear();

    SpritebatchBegin(menu->spritebatch);
    SegmentsDraw(menu->buildings, menu->spritebatch);
    PipeManagerDraw(menu->pipeManager, menu->spritebatch);
    PlayerDraw(menu->player, menu->spritebatch);
    SegmentsDraw(menu->floor, menu->spritebatch);
    SpritebatchEnd(menu->spritebatch);

    WindowRender(menu->window);
}

void MenuDestroy(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    PlayerDestroy(menu->player);
    SegmentsDestroy(menu->floor);
    SegmentsDestroy(menu->buildings);
    PipeManagerDestroy(menu->pipeManager);
}