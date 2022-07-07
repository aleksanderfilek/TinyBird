#include"State.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

StateManager* StateManagerCreate()
{
    StateManager* manager = (StateManager*)calloc(1, sizeof(StateManager));

    #ifdef DEBUG
    printf("[State Manager] Created\n");
    #endif

    return manager;
}

void StateManagerUpdate(void* ptr, double elapsedTime)
{
    StateManager* manager = (StateManager*)ptr;

    if(manager->nextState.size > 0)
    {
        if(manager->currentState.data)
        {
            manager->currentState.destroy(manager->currentState.data);
        }

        manager->currentState = manager->nextState;
        manager->currentState.data = calloc(1, sizeof(manager->currentState.size));
        manager->currentState.start(manager->currentState.data);

        memset(&manager->nextState, 0, sizeof(State));
    }

    if(manager->currentState.data == NULL)
    {
        return;
    }

    manager->currentState.update(manager->currentState.data, elapsedTime);
}

void StateManagerDestroy(void* ptr)
{
    StateManager* manager = (StateManager*)ptr;

    if(manager->currentState.data)
    {
        manager->currentState.destroy(manager->currentState.data);
    }

    free(ptr);

    #ifdef DEBUG
    printf("[State Manager] Destroyed\n");
    #endif
}

void StateManagerSetNext(StateManager* manager, State nextState)
{
    manager->nextState = nextState;
}