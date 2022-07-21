#include"Menu.h"
#include"../Modules/Core.h"
#include"../Modules/Input.h"
#include"../Modules/Window.h"
#include"../Graphics/Shader.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Mesh.h"
#include"../Graphics/Spritebatch.h"
#include"../Graphics/RenderTarget.h"
#include"../ThirdParty/GL/Gl.h"
#include"../Graphics/Font.h"

#include<stdio.h>
#include<stdbool.h>

extern Core* core;

void MenuStart(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    menu->input = CoreModuleGet(core, 1);
    menu->window = CoreModuleGet(core, 2);

    menu->shader = ShaderCreate("bin/resources/spritebatch.vert", "bin/resources/spritebatch.frag");
    menu->texture = TextureCreate("bin/resources/papaj.png");
    menu->mesh = PlaneCreate();
    menu->simpleShader = ShaderCreate("bin/resources/simple.vert", "bin/resources/simple.frag");
    menu->renderTarget = RenderTargetCreate(80,60);

    menu->spritebatch = SpritebatchCreate(menu->shader, 10, 32);

    menu->font = FontCreate("bin/resources/arial.ttf", 0, 48);

    menu->pixelMat = pixelScreenMatrix(640,480);
    menu->smallPixelMat = pixelScreenMatrix(80,60);

    WindowColorSet(0.0, 0.0, 1.0, 1.0);
}

void MenuUpdate(void* ptr, double elapsedTime)
{
    Menu* menu = (Menu*)ptr;

    RenderTargetBind(menu->renderTarget);

    WindowClear();
    SpritebatchBegin(menu->spritebatch);
    ShaderUniformMatrixSet(menu->shader, "pixel", &menu->smallPixelMat);
    SpritebatchDraw(menu->spritebatch, menu->texture, (Int2){0, 0}, (Int2){100, 100}, (Float4){0.0f, 0.0f, 1.0f, 1.0f});
    SpritebatchEnd(menu->spritebatch);

    RenderTargetBind(NULL);
    WindowClear();
    ShaderBind(menu->simpleShader);
    TextureBind(&menu->renderTarget->texture, 0);
    MeshDraw(menu->mesh);

    SpritebatchBegin(menu->spritebatch);
    ShaderUniformMatrixSet(menu->shader, "pixel", &menu->pixelMat);
    SpritebatchRenderText(menu->spritebatch, menu->font, "Alekygi", (Int2){0, 0}, 1.0f);
    SpritebatchEnd(menu->spritebatch);

    WindowRender(menu->window);
}

void MenuDestroy(void* ptr)
{
    Menu* menu = (Menu*)ptr;

    RenderTargetDestroy(menu->renderTarget);
    ShaderDestroy(menu->simpleShader);
    ShaderDestroy(menu->shader);
    TextureDestroy(menu->texture);
    MeshDestroy(menu->mesh);
    SpritebatchDestroy(menu->spritebatch);
    FontDestroy(menu->font);
}