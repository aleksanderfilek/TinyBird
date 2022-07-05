#ifndef TB_CORE_H_
#define TB_CORE_H_

#include"Module.h"
#include"FFData.h"

#include<stdbool.h>
#include<stdint.h>

typedef struct Core
{
    bool quit;

    Module* modules;
    uint32_t* modulesIds;
    uint32_t moduleCapacity;
    uint32_t moduleOffset;

    FFData* ffdata;
    uint32_t* ffdataIds;
    uint32_t ffdataCapacity;
    uint32_t ffdataOffset;
} Core;

Core* CoreCreate();
void CoreStart(Core* core);
void CoreDestroy(Core* core);

void CoreModuleSetup(Core* core, uint32_t startCapacity, uint32_t offset);
void CoreModuleAdd(Core* core, uint32_t id, void* ptr, 
    void (*update)(void* ptr, double elapsedTime), void (*destroy)(void* ptr));
void* CoreModuleGet(Core* core, uint32_t id);
void CoreModuleRemove(Core* core, uint32_t id);

void CoreFFDataSetup(Core* core, uint32_t startCapacity, uint32_t offset);
void CoreFFDataAdd(Core* core, uint32_t id, void *dataPtr, void (*destroy)(void* ptr));
bool CoreFFDataExists(Core* core, uint32_t id);
void* CoreFFDataGet(Core* core, uint32_t id);
void CoreFFDataRemove(Core* core, uint32_t id);

#endif