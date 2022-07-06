#include"Window.h"
#include"Core.h"

#include<stdio.h>
#include<stdlib.h>

extern Core* core;

Window* WindowCreate(const char* title, int width, int height, uint32_t sdlFlag)
{
    Window* window = (Window*)calloc(1, sizeof(Window));

     if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        printf("Window: SDL_Init %s\n", SDL_GetError());
        exit(-1);
    }

    window->sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlFlag | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!window->sdlWindow)
    {
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        return NULL;
    }

    window->id = SDL_GetWindowID(window->sdlWindow);
    
    window->renderer = SDL_CreateRenderer(window->sdlWindow, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!window->renderer)
    {
        printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
        return NULL;
    }

    window->size = (Int2){width, height};
    window->fullScreen = false;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    window->glContext = SDL_GL_CreateContext(window->sdlWindow);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0, 0, width, height);

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    window->closeEvent = EventCreate();

    #ifdef DEBUG
    printf("[Window] Created\n");
    #endif

    return window;
}

void WindowDestroy(void* ptr)
{
    Window* window = (Window*)ptr;

    EventDestroy(window->closeEvent);

    SDL_GL_DeleteContext(window->glContext);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdlWindow);
    free(window);

    #ifdef DEBUG
    printf("[Window] Destroyed\n");
    #endif
}

void WindowUpdate(void* ptr, double elapsedTime)
{
    Window* window = (Window*)ptr;

    while(SDL_PollEvent(&window->sdlEvent) != 0)
    {
        switch (window->sdlEvent.type)
        {
        case SDL_QUIT:
            EventInvoke(window->closeEvent, window, core, 0);
            break;
        }
    }
}

void WindowColorSet(float r, float g, float b, float a)
{
   glClearColor(r, g, b, a); 
}

void WindowClear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void WindowRender(Window* window)
{
    SDL_GL_SwapWindow(window->sdlWindow);
}