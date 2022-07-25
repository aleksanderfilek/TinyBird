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

    game->window = (Window*)CoreModuleGet(core, 2);

    game->player = PlayerCreate((Input*)CoreModuleGet(core, 1), 
        (Int2){ game->window->size.x/3, game->window->size.y/2 });

    game->spritebatch = CoreFFDataGet(core, 2);

    WindowColorSet(0.0f, 0.0f, 1.0f, 1.0f);

    game->floor = SegmentsCreate(game->window->size.x, game->window->size.y, CoreFFDataGet(core, 5));
    game->buildings = SegmentsCreate(game->window->size.x, (int)game->floor->position.y, CoreFFDataGet(core, 6));
    game->pipeManager = PipeManagerCreate((Int2){0,0}, 3, game->window->size.x, game->buildings->position.y);
}

void GameUpdate(void* ptr, double elapsedTime)
{
    Game* game = (Game*)ptr;

    PlayerUpdate(game->player, elapsedTime);
    SegmentsUpdate(game->floor, elapsedTime);
    SegmentsUpdate(game->buildings, elapsedTime);
    PipeManagerUpdate(game->pipeManager, elapsedTime);

    WindowClear();

    SpritebatchBegin(game->spritebatch);
    SegmentsDraw(game->buildings, game->spritebatch);
    PipeManagerDraw(game->pipeManager, game->spritebatch);
    PlayerDraw(game->player, game->spritebatch);
    SegmentsDraw(game->floor, game->spritebatch);
    SpritebatchEnd(game->spritebatch);

    WindowRender(game->window);
}

void GameDestroy(void* ptr)
{
    Game* game = (Game*)ptr;

    PlayerDestroy(game->player);
    SegmentsDestroy(game->floor);
    SegmentsDestroy(game->buildings);
    PipeManagerDestroy(game->pipeManager);
}