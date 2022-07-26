#include"Shader.h"

#include"../ThirdParty/GL/Gl.h"
#include"Debug.h"

#ifdef DEBUG
#include<stdio.h>
#endif

#include<stdlib.h>

Shader* ShaderCreate(const char* vertexPath, const char* fragmentPath)
{
    FILE* vertexFile  = fopen(vertexPath, "r");
    long vertexSize;
    char *vertexBuffer;

    fseek(vertexFile , 0L , SEEK_END);
    vertexSize = ftell(vertexFile);
    rewind(vertexFile);

    vertexBuffer = calloc(1, vertexSize + 1);
    fread(vertexBuffer, vertexSize, 1, vertexFile);

    fclose(vertexFile);

    FILE* fragmentFile  = fopen(fragmentPath, "r");
    long fragmentSize;
    char *fragmentBuffer;

    fseek(fragmentFile , 0L , SEEK_END);
    fragmentSize = ftell(fragmentFile);
    rewind(fragmentFile);

    fragmentBuffer = calloc(1, fragmentSize + 1);
    fread(fragmentBuffer, fragmentSize, 1, fragmentFile);

    fclose(fragmentFile);

    uint32_t program = glCreateProgram();

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const char**)&vertexBuffer, NULL);
    glCompileShader(vertexShader);
    #ifdef DEBUG   
    glShaderCheckError(vertexShader, GL_COMPILE_STATUS);
    #endif
    glAttachShader(program, vertexShader);
    #ifdef DEBUG 
    glProgramCheckError(program, GL_ATTACHED_SHADERS);
    #endif

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char**)&fragmentBuffer, NULL);
    glCompileShader(fragmentShader);
    #ifdef DEBUG  
    glShaderCheckError(fragmentShader, GL_COMPILE_STATUS);
    #endif
    glAttachShader(program, fragmentShader);
    #ifdef DEBUG 
    glProgramCheckError(program, GL_ATTACHED_SHADERS);
    #endif
    
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    free(vertexBuffer);
    free(fragmentBuffer);

    Shader* shader = (Shader*)malloc(sizeof(Shader));

    shader->glId = program;

    #ifdef DEBUG
    printf("[Shader] Created\n");
    #endif

    return shader;
}

void ShaderDestroy(void* ptr)
{
    Shader* shader = (Shader*)ptr;
    glDeleteProgram(shader->glId);
    free(shader);

    #ifdef DEBUG
    printf("[Shader] Destroyed\n");
    #endif
}

void ShaderBind(Shader* shader)
{
    glUseProgram(shader->glId);
}

void ShaderUniformMatrixSet(Shader* shader, const char* name, const Mat4* value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->glId, name), 1, GL_FALSE, &value->column[0].x); 
}

void ShaderUniformVec3Set(Shader* shader, const char* name, Float3 value)
{
    glUniform3f(glGetUniformLocation(shader->glId, name), value.x, value.y, value.z);
}