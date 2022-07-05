#include"Modules/Core.h"
#include"Modules/Window.h"
#include"Modules/Input.h"
#include"Modules/State.h"
#include"States/Menu.h"

Core* core = NULL;

#include<stdio.h>

int WinMain(int argc, char *argv[])
{
    core = CoreCreate();
    Window* window = WindowCreate("title", 640, 480, 0);
    Input* input = InputCreate();
    StateManager* stateManager = StateManagerCreate();
    StateManagerSetNext(stateManager, MenuState);

    CoreModuleSetup(core, 3, 1);
    CoreModuleAdd(core, 1, input, InputUpdate, InputDestroy);
    CoreModuleAdd(core, 2, window, WindowUpdate, WindowDestroy);
    CoreModuleAdd(core, 3, stateManager, StateManagerUpdate, StateManagerDestroy);

    CoreStart(core);
    CoreDestroy(core);

    return 0;
}