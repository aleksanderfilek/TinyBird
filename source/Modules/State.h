#ifndef TB_STATE_H_
#define TB_STATE_H_

#include<stdint.h>

typedef struct State
{
    void* data;
    uint32_t size;
    void (*start)(void* ptr);
    void (*update)(void* ptr, double elapsed);
    void (*destroy)(void* ptr);
} State;

typedef struct StateManager
{
    State currentState;
    State nextState;
} StateManager;

StateManager* StateManagerCreate();
void StateManagerUpdate(void* ptr, double elapsedTime);
void StateManagerDestroy(void* ptr);

void StateManagerSetNext(StateManager* manager, State nextState);

#endif