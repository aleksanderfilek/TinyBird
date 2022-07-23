#ifndef TB_MATH_H_
#define TB_MATH_H_

#include<stdint.h>

int LerpI(int a, int b, float t);

typedef struct Int2
{
    int x, y;
} Int2;

typedef struct Float2
{
    float x, y;
} Float2;

Float2 LerpF2(Float2 a, Float2 b, float t);
Int2 Float2ToInt2(Float2 a);

typedef struct Float3
{
    float x, y, z;
} Float3;

typedef struct Float4
{
    float x, y, z, w;
} Float4;

typedef struct Mat4
{
    Float4 column[4];
} Mat4;

Mat4 pixelScreenMatrix(int width, int height);

#endif