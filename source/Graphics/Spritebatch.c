#include"Spritebatch.h"
#include"../ThirdParty/GL/Gl.h"
#include"Texture.h"
#include"Shader.h"

#ifdef DEBUG
#include<stdio.h>
#endif
#include<stdlib.h>

Spritebatch* SpritebatchCreate(Shader* shader, uint32_t capacity, uint32_t maxTextures)
{
  Spritebatch* spritebatch = (Spritebatch*)malloc(sizeof(Spritebatch));

  ShaderBind(shader);
  spritebatch->shader = shader;
  spritebatch->shaderTexturesLocation = glGetUniformLocation(shader->glId, "sb_textures");

  spritebatch->spriteCapacity = capacity;
  spritebatch->quadBuffer = (SpritebatchVertex*)malloc(4 * capacity * sizeof(SpritebatchVertex));
  spritebatch->quadBufferPtr = spritebatch->quadBuffer;
  
  glCreateVertexArrays(1, &spritebatch->VAO);
  glBindVertexArray(spritebatch->VAO);

  glCreateBuffers(1, &spritebatch->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, spritebatch->VBO);
  glBufferData(GL_ARRAY_BUFFER, 4 * capacity * sizeof(SpritebatchVertex), NULL, GL_DYNAMIC_DRAW);  

  glEnableVertexArrayAttrib(spritebatch->VAO, 0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)0);

  glEnableVertexArrayAttrib(spritebatch->VAO, 1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)(sizeof(Float2)));

  glEnableVertexArrayAttrib(spritebatch->VAO, 2);
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)(sizeof(Float2) + sizeof(Float2)));

  spritebatch->indexCount = 0;
  spritebatch->maxIndexCount = 6 * capacity;
  uint32_t indices[spritebatch->maxIndexCount];
  uint32_t offset = 0;
  for(int i = 0; i < spritebatch->maxIndexCount; i+=6)
  {
    indices[i + 0] = 0 + offset;
    indices[i + 1] = 1 + offset;
    indices[i + 2] = 2 + offset;

    indices[i + 3] = 2 + offset;
    indices[i + 4] = 3 + offset;
    indices[i + 5] = 0 + offset;

    offset += 4;
  }

  glCreateBuffers(1, &spritebatch->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spritebatch->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

  spritebatch->maxTextureSlots = maxTextures;
  spritebatch->textureSlots = (const Texture**)calloc(maxTextures, sizeof(const Texture*));
  spritebatch->textureSlotIndex = 0;

  spritebatch->sampler = (int*)calloc(maxTextures, sizeof(int));
  for(int i = 0; i < maxTextures; i++)
  {
    spritebatch->sampler[i] = i;
  }

  #ifdef DEBUG
  printf("[Spritebatch] Created\n");
  #endif

  return spritebatch;
}

void SpritebatchDestroy(void* ptr)
{
  Spritebatch* spritebatch = (Spritebatch*)ptr;
  free(spritebatch->textureSlots);

  glDeleteVertexArrays(1, &spritebatch->VAO);
  glDeleteBuffers(1, &spritebatch->VBO);
  glDeleteBuffers(1, &spritebatch->EBO);

  free(spritebatch->quadBuffer);
  free(spritebatch->sampler);
  free(ptr);

  #ifdef DEBUG
  printf("[Spritebatch] Destroyed\n");
  #endif
}

void SpritebatchBegin(Spritebatch* spritebatch)
{
  glUniform1iv(spritebatch->shaderTexturesLocation, spritebatch->maxTextureSlots, spritebatch->sampler);

  spritebatch->quadBufferPtr = spritebatch->quadBuffer;

  spritebatch->indexCount = 0;
  spritebatch->textureSlotIndex = 0;

  ShaderBind(spritebatch->shader);
}

void SpritebatchEnd(Spritebatch* spritebatch)
{
  GLsizeiptr size = (uint8_t*)spritebatch->quadBufferPtr - (uint8_t*)spritebatch->quadBuffer;
  glBindBuffer(GL_ARRAY_BUFFER, spritebatch->VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, spritebatch->quadBuffer);

  for(int i = 0; i < spritebatch->textureSlotIndex; i++)
  {
    glBindTextureUnit(i, spritebatch->textureSlots[i]->glId);
  }

  glBindVertexArray(spritebatch->VAO);
  glDrawElements(GL_TRIANGLES, spritebatch->indexCount, GL_UNSIGNED_INT, NULL);
}

void SpritebatchDraw(Spritebatch* spritebatch, Texture* texture, const Int2 position, const Int2 size, Float4 rect)
{
  if(spritebatch->indexCount >= spritebatch->maxIndexCount || spritebatch->textureSlotIndex > spritebatch->maxTextureSlots)
  {
    SpritebatchEnd(spritebatch);
    SpritebatchBegin(spritebatch);
  }

  float textureIndex = -1.0f;
  // check registred texture
  for(int i = 0; i < spritebatch->textureSlotIndex; i++)
  {
    if(spritebatch->textureSlots[i]->glId == texture->glId)
    {
      textureIndex = (float)i;
      break;
    }
  }

  // // add texture if not registered
  if(textureIndex == -1.0f)
  {
    textureIndex = spritebatch->textureSlotIndex;
    spritebatch->textureSlots[spritebatch->textureSlotIndex] = texture;
    spritebatch->textureSlotIndex++;
  }

  spritebatch->quadBufferPtr->position = (Float2){ (float)position.x, (float)position.y };
  spritebatch->quadBufferPtr->texCoords = (Float2){ rect.x, rect.y };
  spritebatch->quadBufferPtr->texIndex = textureIndex;
  spritebatch->quadBufferPtr++;

  spritebatch->quadBufferPtr->position = (Float2){ (float)(position.x + size.x), (float)position.y };
  spritebatch->quadBufferPtr->texCoords = (Float2){ rect.z, rect.y };
  spritebatch->quadBufferPtr->texIndex = textureIndex;
  spritebatch->quadBufferPtr++;

  spritebatch->quadBufferPtr->position = (Float2){ (float)(position.x + size.x), (float)(position.y + size.y) };
  spritebatch->quadBufferPtr->texCoords = (Float2){ rect.z, rect.w };
  spritebatch->quadBufferPtr->texIndex = textureIndex;
  spritebatch->quadBufferPtr++;

  spritebatch->quadBufferPtr->position = (Float2){ (float)position.x, (float)(position.y + size.y) };
  spritebatch->quadBufferPtr->texCoords = (Float2){ rect.x, rect.w };
  spritebatch->quadBufferPtr->texIndex = textureIndex;
  spritebatch->quadBufferPtr++;

  spritebatch->indexCount += 6;
}