#include"Font.h"
#include"../ThirdParty/GL/Gl.h"
#include"../ThirdParty/FreeType/FreeType.h"

#include<stdlib.h>
#include<string.h>

#ifdef DEBUG
#include<stdio.h>
#endif

Font* FontCreate(const char* path, int width, int height)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        #ifdef DEBUG
        printf("ERROR::FREETYPE: Could not init FreeType Library\n");
        #endif

        return NULL;
    }

    Font* font = (Font*)malloc(sizeof(Font));
    font->height = height;

    FT_Face face;
    if (FT_New_Face(ft, path, 0, &face))
    {
        #ifdef DEBUG
        printf("ERROR::FREETYPE: Failed to load font\n");
        #endif
        return NULL;
    }

    FT_Set_Pixel_Sizes(face, width, height);  

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            #ifdef DEBUG
            printf("ERROR::FREETYTPE: Failed to load Glyph\n");
            #endif
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = (Character){
            texture, 
            (Int2){face->glyph->bitmap.width, face->glyph->bitmap.rows},
            (Int2){face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x
        };
        font->characters[c] = character;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    #ifdef DEBUG
    printf("[Font] Created\n");
    #endif

    return font;
}

void FontDestroy(void* ptr)
{
    Font* font = (Font*)ptr;

    for(int i = 0; i < 128; i++)
    {
        glDeleteTextures(1, &font->characters[i].TextureID);
    }

    #ifdef DEBUG
    printf("[Font] Destroyed\n");
    #endif
}

Int2 FontTextSize(Font* font, const char* text, float scale)
{
    Int2 size = { 0, font->height };

    int length = strlen(text);
    for(int i = 0; i < length; i++)
    {
        Character* character = &font->characters[(int)text[i]];
        size.x += (character->Advance >> 6 ) * scale;
        int ySize = character->Size.y * scale;
        if(ySize > size.y)
        {
            size.y = ySize;
        }
    }

    return size;
}