#ifndef TB_FONT_H_
#define TB_FONT_H_

#include"../Math.h"

typedef struct Character 
{
    unsigned int TextureID;
    Int2 Size;
    Int2 Bearing;
    unsigned int Advance;
} Character;

typedef struct Font
{
    Character characters[128];
    int height;
} Font;

Font* FontCreate(const char* path, int width, int height);
void FontDestroy(void* ptr);

#endif