#include"Core.h"

#include"../ThirdParty/SDL2/SDL.h"

#include<stdio.h>
#include<stdlib.h>

Core* CoreCreate(uint32_t moduleCapacity)
{
    Core* core = (Core*)calloc(1, sizeof(Core));

    core->quit = 0;
    core->ffdataOffset = 1;

    #ifdef DEBUG
    printf("[Core] Created\n");
    #endif

    return core;
}

void CoreStart(Core* core)
{
    if(SDL_Init(SDL_INIT_TIMER) < 0)
    {
        printf("[Core] - SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    uint32_t timer = 0;
    double deltaTime = 0.0;

    while(core->quit == false)
    {
        timer = SDL_GetTicks();

        for(int i = 0; i < core->moduleCapacity; i++)
        {
            if(core->modules[i].update == NULL)
            {
                continue;
            }

            core->modules[i].update(core->modules[i].data, deltaTime);
        }

        deltaTime = (double)(SDL_GetTicks() - timer)/1000.0;
    }
}

void CoreDestroy(Core* core)
{
    for(int i = 0; i < core->moduleCapacity; i++)
    {
        if(core->modules[i].destroy == NULL)
        {
            continue;
        }

        core->modules[i].destroy(core->modules[i].data);
    }

    for(int i = 0; i < core->ffdataCapacity; i++)
    {
        if(core->ffdata[i].destroy == NULL)
        {
            continue;
        }

        core->ffdata[i].destroy(core->ffdata[i].ptr);
    }

    SDL_Quit();

    free(core);

    #ifdef DEBUG
    printf("[Core] Destroyed\n");
    #endif
}

void CoreModuleSetup(Core* core, uint32_t startCapacity, uint32_t offset)
{
    core->modules = (Module*)calloc(startCapacity, sizeof(Module));
    core->modulesIds = (uint32_t*)calloc(startCapacity, sizeof(uint32_t));
    core->moduleCapacity = startCapacity;
    core->moduleOffset = offset;
}

void CoreModuleAdd(Core* core, uint32_t id, void* ptr, 
    void (*update)(void* ptr, double elapsedTime), void (*destroy)(void* ptr))
{
    int firstEmpty;
    for(firstEmpty = 0; firstEmpty < core->moduleCapacity; firstEmpty++)
    {
        uint32_t tempId = core->modulesIds[firstEmpty];
        if(tempId == 0 || tempId == id)
        {
            break;   
        }
    }

    if(firstEmpty >= core->moduleCapacity)
    {
        core->moduleCapacity += core->moduleOffset;
        core->modules = (Module*)realloc(core->modules, core->moduleCapacity * sizeof(Module));
        core->modulesIds = (uint32_t*)realloc(core->modulesIds, core->moduleCapacity * sizeof(uint32_t));
    }

    #ifdef DEBUG
    if(destroy == NULL)
    {
        printf("[Core][Module] Added element with id %d has no destroy function.\n", id);
    }
    #endif

    core->modulesIds[firstEmpty] = id;
    core->modules[firstEmpty] = (Module){ ptr, update, destroy };
}

void* CoreModuleGet(Core* core, uint32_t id)
{
    for(int i = 0; i < core->moduleCapacity; i++)
    {
        if(core->modulesIds[i] == id)
        {
            return core->modules[i].data;
        }
    }

    return NULL;
}

void CoreModuleRemove(Core* core, uint32_t id)
{
    int i;
    for(i = 0; i < core->moduleCapacity; i++)
    {
        if(core->modulesIds[i] == id)
        {
            break;
        }
    }

    if(i == core->moduleCapacity)
    {
        return;
    }

    core->modules[i] = (Module){ NULL, NULL, NULL };
    core->modulesIds[i] = 0;
}

void CoreFFDataSetup(Core* core, uint32_t startCapacity, uint32_t offset)
{
    core->ffdata = (FFData*)calloc(startCapacity, sizeof(FFData));
    core->ffdataIds = (uint32_t*)calloc(startCapacity, sizeof(uint32_t));
    core->ffdataCapacity = startCapacity;
    core->ffdataOffset = offset;
}

void CoreFFDataAdd(Core* core, uint32_t id, void *dataPtr, void (*destroy)(void* ptr))
{
    int firstEmpty;
    for(firstEmpty = 0; firstEmpty < core->ffdataCapacity; firstEmpty++)
    {
        uint32_t tempId = core->ffdataIds[firstEmpty];
        if(tempId == 0 || tempId == id)
        {
            break;   
        }
    }

    if(firstEmpty >= core->ffdataCapacity)
    {
        core->ffdataCapacity += core->ffdataOffset;
        core->ffdata = (FFData*)realloc(core->ffdata, core->ffdataCapacity * sizeof(FFData));
        core->ffdataIds = (uint32_t*)realloc(core->ffdataIds, core->ffdataCapacity * sizeof(uint32_t));
    }

    #ifdef DEBUG
    if(destroy == NULL)
    {
        printf("[Core][FFData] Added element with id %d has no destroy function.\n", id);
    }
    #endif

    core->ffdataIds[firstEmpty] = id;
    core->ffdata[firstEmpty] = (FFData){ dataPtr, destroy };
}

bool CoreFFDataExists(Core* core, uint32_t id)
{
    for(int i = 0; i < core->ffdataCapacity; i++)
    {
        if(core->ffdataIds[i] == id)
        {
            return true;
        }
    }

    return false;
}

void* CoreFFDataGet(Core* core, uint32_t id)
{
    for(int i = 0; i < core->ffdataCapacity; i++)
    {
        if(core->ffdataIds[i] == id)
        {
            return core->ffdata[i].ptr;
        }
    }

    return NULL;
}

void CoreFFDataRemove(Core* core, uint32_t id)
{
    int i;
    for(i = 0; i < core->ffdataCapacity; i++)
    {
        if(core->ffdataIds[i] == id)
        {
            break;
        }
    }

    if(i == core->ffdataCapacity)
    {
        return;
    }

    core->ffdata[i] = (FFData){ NULL, NULL };
    core->ffdataIds[i] = 0;
}