#include"Texture.h"

#include"../ThirdParty/GL/Gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../ThirdParty/Stb/stb_image.h"

#include<stdlib.h>
#include<stdio.h>

Texture* TextureCreate(const char* path)
{
    int width, height, nrChannels;
    uint8_t *data = stbi_load(path, &width, &height, &nrChannels, 0); 

    uint32_t gl_id;
    glGenTextures(1, &gl_id);
    glBindTexture(GL_TEXTURE_2D, gl_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    Texture* texture = (Texture*)malloc(sizeof(Texture));
    texture->glId = gl_id;
    texture->size = (Int2){ width, height };

    return texture;
}

void TextureDestroy(Texture* texture)
{
    glDeleteTextures(1, &texture->glId);
}

void TextureBind(Texture* texture, uint32_t textureSlotId)
{
    glActiveTexture(GL_TEXTURE0 + textureSlotId);
    glBindTexture(GL_TEXTURE_2D, texture->glId);
}