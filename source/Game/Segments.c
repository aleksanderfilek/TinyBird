#include"Segments.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Spritebatch.h"

#include<stdlib.h>

Segments* SegmentsCreate(int screenWidth, int screenHeight, const char* texturePath)
{
    Segments* segments = (Segments*)malloc(sizeof(Segments));
    segments->texture = TextureCreate(texturePath);
    segments->segmentsCount = 1 + screenWidth / segments->texture->size.x;
    segments->position = (Float2){ 0.0f, screenHeight - segments->texture->size.y };

    return segments;
}

void SegmentsUpdate(Segments* segments, double elapsedTime)
{
    segments->position.x -= Segments_SPEED * elapsedTime;

    if(segments->position.x <= -segments->texture->size.x)
    {
        segments->position.x = 0.0f;
    }
}

void SegmentsDraw(Segments* segments, Spritebatch* spritebatch)
{
    for(int i = 0; i < segments->segmentsCount; i++)
    {
        Int2 position = { segments->position.x + segments->texture->size.x * i, segments->position.y };
        SpritebatchDraw(spritebatch, segments->texture, position, segments->texture->size, (Float4){0.0f, 0.0f, 1.0f, 1.0f});
    }
}

void SegmentsDestroy(Segments* segments)
{
    TextureDestroy(segments->texture);
    free(segments);
}