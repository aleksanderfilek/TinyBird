#ifndef TB_TEXTURE_H_
#define TB_TEXTURE_H_

#include"../Math.h"
#include"Color.h"

#include<stdint.h>

typedef struct Texture
{
    uint32_t glId;
    Int2 size;
} Texture;

Texture* TextureCreate(const char* path);
void TextureDestroy(void* ptr);
void TextureBind(Texture* texture, uint32_t textureSlotId);

#endif