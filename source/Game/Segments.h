#ifndef Segments_H_
#define Segments_H_

#include"../Defaults.h"
#include"../Math.h"

#define Segments_SPEED 80

STRUCT(Texture);
STRUCT(Spritebatch);

typedef struct Segments
{
   Texture* texture; 

    Float2 position;
    int segmentsCount;

} Segments;

Segments* SegmentsCreate(int screenWidth, int screenHeight, Texture* texture);
void SegmentsUpdate(Segments* segments, double elapsedTime);
void SegmentsDraw(Segments* segments, Spritebatch* spritebatch);
void SegmentsDestroy(Segments* segments);

#endif