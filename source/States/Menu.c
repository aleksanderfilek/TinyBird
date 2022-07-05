#include"Menu.h"
#include"../Modules/Core.h"
#include"../Modules/Input.h"
#include"../Modules/Window.h"
#include"../Graphics/Shader.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Mesh.h"

#include<stdio.h>

extern Core* core;

void MenuStart(void* ptr)
{
    Menu* menu = (Menu*)ptr;
    menu->input = CoreModuleGet(core, 1);
    menu->window = CoreModuleGet(core, 2);
    menu->shader = ShaderCreate("bin/resources/simple.vert", "bin/resources/simple.frag");
    menu->texture = TextureCreate("bin/resources/papaj.png");
    menu->mesh = PlaneCreate();

    ShaderBind(menu->shader);

    glClearColor(0.0, 0.0, 1.0, 1.0);
}

void MenuUpdate(void* ptr, double elapsedTime)
{
    Menu* menu = (Menu*)ptr;

    if(InputKeyDown(menu->input, KEYCODE_A))
    {
        printf("quit\n");
        core->quit = true;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    TextureBind(menu->texture, 0);
    MeshDraw(menu->mesh);

    SDL_GL_SwapWindow(menu->window->sdlWindow);
}

void MenuDestroy(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    ShaderDestroy(menu->shader);
    TextureDestroy(menu->texture);
    MeshDestroy(menu->mesh);
    free(ptr);
}