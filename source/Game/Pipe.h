#ifndef PIPE_H_
#define PIPE_H_

#include"../Defaults.h"
#include"../Math.h"

#define PIPE_SPEED 80

STRUCT(Texture);
STRUCT(Spritebatch);

typedef struct Pipe
{
    Float2 position;
} Pipe;

typedef struct PipeManager
{
    Pipe* pipes;
    int pipesCount;
    Int2 screenSize;
    int gapCount;
    Texture* texture;
} PipeManager;

PipeManager* PipeManagerCreate(Int2 gapBounds, int count, int screenWidth, int screenHeight);
void PipeManagerDestroy(PipeManager* manager);
void PipeManagerUpdate(PipeManager* manager, double elapsedTime);
void PipeManagerDraw(PipeManager* manager, Spritebatch* spritebatch);

#endif