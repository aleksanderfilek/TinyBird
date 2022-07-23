#include"Math.h"

#include<string.h>

int LerpI(int a, int b, float t)
{
    return a + (b-a)*t;
}

Float2 LerpF2(Float2 a, Float2 b, float t)
{
    return (Float2){ a.x + t*(b.x - a.x), a.y + t*(b.y - a.y) };
}

Int2 Float2ToInt2(Float2 a)
{
    return (Int2){ (int)a.x, (int)a.y };
}

Mat4 pixelScreenMatrix(int width, int height)
{
    Mat4 matrix;
    memset(&matrix, 0, sizeof(Mat4));
    matrix.column[0].x = 2.0f/width;
    matrix.column[1].y = -2.0f/height;
    matrix.column[2].z = 1.0f;
    matrix.column[3].x = -1;
    matrix.column[3].y = 1;
    matrix.column[3].z = 0.0f;
    matrix.column[3].w = 1;
    return matrix;
}