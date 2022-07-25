#include"Pipe.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Spritebatch.h"

#include<time.h>
#include<stdlib.h>
#include<math.h>


PipeManager* PipeManagerCreate(Int2 gapBounds, int count, int screenWidth, int screenHeight)
{
    srand(time(NULL));

    PipeManager* manager = (PipeManager*)malloc(sizeof(PipeManager));

    manager->texture = TextureCreate("bin/resources/Pipe.png");

    manager->screenSize = (Int2){screenWidth, screenHeight};
    manager->pipesCount = count;
    manager->pipes = (Pipe*)malloc(count * sizeof(Pipe));
    manager->gapCount = (screenHeight - 128) / 32;
    int xDistance = (screenWidth + 32) / count;
    for(int i = 0; i < manager->pipesCount; i++)
    {
        manager->pipes[i].position.x = i * xDistance + (count-1)*xDistance;
        int j = rand()%manager->gapCount;
        manager->pipes[i].position.y = 128 + (32 * j);
    }
    return manager;
}

void PipeManagerDestroy(PipeManager* manager)
{
    TextureDestroy(manager->texture);
    free(manager);
}

void PipeManagerUpdate(PipeManager* manager, double elapsedTime)
{
    for(int i = 0; i < manager->pipesCount; i++)
    {
        Pipe* pipe = &manager->pipes[i];

        pipe->position.x -= PIPE_SPEED * elapsedTime;

        if(pipe->position.x <= -32)
        {
            pipe->position.x = manager->screenSize.x;
            int j = rand()%manager->gapCount;
            pipe->position.y = 128 + (32 * j);
        }
    }
}

void PipeManagerDraw(PipeManager* manager, Spritebatch* spritebatch)
{
    Pipe* pipe = NULL;
    for(int i = 0; i < manager->pipesCount; i++)
    {
        pipe = &manager->pipes[i];
        int yPos = pipe->position.y;
        Int2 position;
        int count = (manager->screenSize.y + 96 - pipe->position.y + manager->texture->size.y) / manager->texture->size.y;
        SpritebatchDraw(spritebatch, manager->texture, Float2ToInt2(pipe->position), (Int2){32,32}, (Float4){0.0f, 0.0f, 0.5f, 1.0f});
        for(int i = 0; i < count; i++)
        {
            yPos += manager->texture->size.y;
            position = (Int2){ (int)pipe->position.x, yPos };
            SpritebatchDraw(spritebatch, manager->texture, position, (Int2){32,32}, (Float4){0.5f, 0.0f, 1.0f, 1.0f});
        }

        yPos = pipe->position.y - 112;
        position = (Int2){ (int)pipe->position.x, yPos };
        SpritebatchDraw(spritebatch, manager->texture, position, (Int2){32,32}, (Float4){0.0f, 0.0f, 0.5f, -1.0f});
        count = ceilf((float)yPos / (float)manager->texture->size.y);
        for(int i = 0; i < count; i++)
        {
            yPos -= manager->texture->size.y;
            position = (Int2){ (int)pipe->position.x, yPos };
            SpritebatchDraw(spritebatch, manager->texture, position, (Int2){32,32}, (Float4){0.5f, 0.0f, 1.0f, 1.0f});
        }
    }
}