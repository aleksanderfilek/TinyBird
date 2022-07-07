#include"RenderTarget.h"
#include"../ThirdParty/GL/Gl.h"
#include"../Modules/Core.h"
#include"../Modules/Window.h"

#include<stdlib.h>
#include<stdio.h>
extern Core* core;

RenderTarget* RenderTargetCreate(int width, int height)
{
  uint32_t id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  

  uint32_t fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  RenderTarget* renderTarget = (RenderTarget*)malloc(sizeof(RenderTarget));

  renderTarget->texture.glId = id;
  renderTarget->texture.size = (Int2){ width, height };
  renderTarget->fbo = fbo;

  return renderTarget;
}

void RenderTargetDestroy(void* ptr)
{
  RenderTarget* renderTarget = (RenderTarget*)ptr;
  glDeleteTextures(1, &renderTarget->texture.glId);
  glDeleteFramebuffers(1, &renderTarget->fbo);

  free(ptr);
}

void RenderTargetBind(RenderTarget* renderTarget)
{
  int id = (renderTarget)? renderTarget->fbo : 0;
  glBindFramebuffer(GL_FRAMEBUFFER, id);

  if(renderTarget)
  {
    glViewport(0, 0, renderTarget->texture.size.x, renderTarget->texture.size.y);
    return;
  }

  Int2 size = ((Window*)CoreModuleGet(core, 2))->size;
  glViewport(0, 0, size.x, size.y);
}