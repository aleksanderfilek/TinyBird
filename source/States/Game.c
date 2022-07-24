#include"Game.h"
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

void GameStart(void* ptr)
{
    Game* game = (Game*)ptr;

    // menu->window = (Window*)CoreModuleGet(core, 2);

    // menu->player = PlayerCreate((Input*)CoreModuleGet(core, 1), 
    //     (Int2){ menu->window->size.x/3, menu->window->size.y/2 });

    // Shader* shader = NULL;
    // if(!CoreFFDataExists(core, 1))
    // {
    //     Shader* shader = ShaderCreate("bin/resources/spritebatch.vert", "bin/resources/spritebatch.frag");
    //     CoreFFDataAdd(core, 1, shader, ShaderDestroy);
    //     Mat4 pixelMat = pixelScreenMatrix(menu->window->size.x, menu->window->size.y);
    //     ShaderBind(shader);
    //     ShaderUniformMatrixSet(shader, "pixel", &pixelMat);
    // }
    // else
    // {
    //     shader = (Shader*)CoreFFDataGet(core, 0);
    // }

    // if(!CoreFFDataExists(core, 2))
    // {
    //     menu->spritebatch = SpritebatchCreate(shader, 10, 32);
    //     CoreFFDataAdd(core, 2, shader, ShaderDestroy);
    // }
    // else
    // {
    //     menu->spritebatch = CoreFFDataGet(core, 2);
    // }

    // WindowColorSet(0.0f, 0.0f, 1.0f, 1.0f);

    // menu->floor = SegmentsCreate(menu->window->size.x, menu->window->size.y, "bin/resources/Floor.png");
    // menu->buildings = SegmentsCreate(menu->window->size.x, (int)menu->floor->position.y, "bin/resources/Buildings.png");
    // menu->pipeManager = PipeManagerCreate((Int2){0,0}, 3, menu->window->size.x, menu->buildings->position.y);

}

void GameUpdate(void* ptr, double elapsedTime)
{
    Game* game = (Game*)ptr;

    // PlayerUpdate(menu->player, elapsedTime);
    // SegmentsUpdate(menu->floor, elapsedTime);
    // SegmentsUpdate(menu->buildings, elapsedTime);
    // PipeManagerUpdate(menu->pipeManager, elapsedTime);

    // WindowClear();

    // SpritebatchBegin(menu->spritebatch);
    // SegmentsDraw(menu->buildings, menu->spritebatch);
    // PipeManagerDraw(menu->pipeManager, menu->spritebatch);
    // PlayerDraw(menu->player, menu->spritebatch);
    // SegmentsDraw(menu->floor, menu->spritebatch);
    // SpritebatchEnd(menu->spritebatch);

    // WindowRender(menu->window);
}

void GameDestroy(void* ptr)
{
    Game* game = (Game*)ptr;

    // PlayerDestroy(game->player);
    // SegmentsDestroy(game->floor);
    // SegmentsDestroy(game->buildings);
    // PipeManagerDestroy(game->pipeManager);
}