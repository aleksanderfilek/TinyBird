#ifndef TB_SHADER_H_
#define TB_SHADER_H_

#include"../Math.h"

#include<stdint.h>

typedef struct Shader
{
    uint32_t glId;
} Shader;

Shader* ShaderCreate(const char* vertexPath, const char* fragmentPath);
void ShaderDestroy(void* ptr);
void ShaderBind(Shader* shader);

void ShaderUniformMatrixSet(Shader* shader, const char* name, const Mat4* value);

#endif