#ifndef TB_RENDERTARGET_H_
#define TB_RENDERTARGET_H_

#include"../Defaults.h"
#include"Texture.h"
#include"../Math.h"

#include<stdint.h>

typedef struct RenderTarget
{
  Texture texture;
  uint32_t fbo;
} RenderTarget;

RenderTarget* RenderTargetCreate(int width, int height);
void RenderTargetDestroy(void* ptr);

void RenderTargetBind(RenderTarget* renderTarget);

#endif