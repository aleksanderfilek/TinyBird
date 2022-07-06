#ifndef TB_WINDOW_H_
#define TB_WINDOW_H_

#include"../Math.h"
#include"../ThirdParty/SDL2/SDL.h"
#include"../ThirdParty/GL/Gl.h"
#include"../ThirdParty/SDL2/SDL_opengl.h"
#include"../Event.h"

#include<stdbool.h>
#include<stdint.h>

typedef struct Window
{
    uint32_t id;
    Int2 size;
    bool fullScreen;

    SDL_Window* sdlWindow;
    SDL_Renderer* renderer;
    SDL_GLContext glContext;
    SDL_Event sdlEvent;

    Event* closeEvent;
} Window;

Window* WindowCreate(const char* title, int width, int height, uint32_t sdlFlag);
void WindowUpdate(void* ptr, double elapsedTime);
void WindowDestroy(void* ptr);

void WindowColorSet(float r, float g, float b, float a);
void WindowClear();
void WindowRender(Window* window);

#endif