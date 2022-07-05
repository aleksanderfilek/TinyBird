#include"Math.h"

#include<string.h>

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