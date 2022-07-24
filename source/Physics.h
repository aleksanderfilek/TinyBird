#ifndef TB_PHYSICS_H_
#define TB_PHYSICS_H_

#include"Math.h"

#include<stdbool.h>

typedef struct BoxCollision2D
{
    Int2* position;
    Int2* size;
} BoxCollision2D;

bool PointBoxIntersection(Int2 point, BoxCollision2D box);

typedef struct CircleCollision2D
{
    Int2* position;
    int radius;
} CircleCollision2D;

#endif