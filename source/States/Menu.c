#include"Menu.h"
#include"../Modules/Core.h"
#include"../Modules/Input.h"
#include"../Modules/Window.h"
#include"../Graphics/Shader.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Mesh.h"
#include"../Graphics/Spritebatch.h"
#include<stdio.h>

extern Core* core;

void MenuStart(void* ptr)
{
    Menu* menu = (Menu*)ptr;
    menu->input = CoreModuleGet(core, 1);
    menu->window = CoreModuleGet(core, 2);
    menu->shader = ShaderCreate("bin/resources/simple.vert", "bin/resources/simple.frag");
    menu->texture = TextureCreate("bin/resources/papaj.png");
    //menu->mesh = PlaneCreate();

    menu->spritebatch = SpritebatchCreate(menu->shader, 10, 2);

    ShaderBind(menu->shader);
    Mat4 pixelMat = pixelScreenMatrix(640, 480);
    ShaderUniformMatrixSet(menu->shader, "pixel", &pixelMat);

    glClearColor(0.0, 0.0, 1.0, 1.0);
}

void MenuUpdate(void* ptr, double elapsedTime)
{
    Menu* menu = (Menu*)ptr;
    
    glClear(GL_COLOR_BUFFER_BIT);
    SpritebatchBegin(menu->spritebatch);
        //TextureBind(menu->texture, 0);
        //MeshDraw(menu->mesh);
    SpritebatchDraw(menu->spritebatch, menu->texture, (Int2){20, 20}, (Int2){100, 100}, (Float4){0.0f, 0.0f, 1.0f, 1.0f});

    SpritebatchEnd(menu->spritebatch);
    SDL_GL_SwapWindow(menu->window->sdlWindow);
}

void MenuDestroy(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    ShaderDestroy(menu->shader);
    TextureDestroy(menu->texture);
    //MeshDestroy(menu->mesh);
    SpritebatchDestroy(menu->spritebatch);
    free(ptr);
}