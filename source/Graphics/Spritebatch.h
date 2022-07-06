#ifndef TB_SPRITEBATCH_H_
#define TB_SPRITEBATCH_H_

#include"../Defaults.h"
#include"../Math.h"

#include<stdint.h>

STRUCT(Texture);
STRUCT(Shader);

typedef struct SpritebatchVertex
{
  Float2 position;
  Float2 texCoords;
  float texIndex;
} SpritebatchVertex;

typedef struct Spritebatch
{
  uint32_t spriteCapacity;

  uint32_t VAO;
  uint32_t VBO;
  uint32_t EBO;

  SpritebatchVertex* quadBuffer;
  SpritebatchVertex* quadBufferPtr;

  uint32_t indexCount;
  uint32_t maxIndexCount;

  uint32_t maxTextureSlots;
  const Texture** textureSlots;
  uint32_t textureSlotIndex;
  uint32_t shaderTexturesLocation;

  int *sampler;
  Shader* shader;
} Spritebatch;

Spritebatch* SpritebatchCreate(Shader* shader, uint32_t capacity, uint32_t maxTextures);
void SpritebatchDestroy(void* ptr);
void SpritebatchBegin(Spritebatch* spritebatch);
void SpritebatchEnd(Spritebatch* spritebatch);
void SpritebatchDraw(Spritebatch* spritebatch, Texture* texture, const Int2 position, const Int2 size, Float4 rect);

#endif