#ifndef TB_SHADER_H_
#define TB_SHADER_H_

#include<stdint.h>

typedef struct Shader
{
    uint32_t glId;
} Shader;

Shader* ShaderCreate(const char* vertexPath, const char* fragmentPath);
void ShaderDestroy(Shader* shader);
void ShaderBind(Shader* shader);

#endif