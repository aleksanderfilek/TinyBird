#include"Debug.h"

#include<stdio.h>

GLint glShaderCheckError_(GLuint shader, GLenum pname ,const char *file, int line)
{
    GLint errorCode;
    glGetShaderiv(shader, pname, &errorCode);
    if(!errorCode)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);

        GLint shaderType;
        glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
        switch(shaderType)
        {
        case GL_VERTEX_SHADER:
            printf("Error: Vertex Shader - ");
            break;
        case GL_GEOMETRY_SHADER:
            printf("Error: Geometry Shader - ");
            break;
        case GL_FRAGMENT_SHADER:
            printf("Error: Fragment Shader - ");
            break;
        }

        switch (pname)
        {
        case  GL_DELETE_STATUS :
            printf("Delete Status Failed ");
            break;
        case  GL_COMPILE_STATUS :
            printf("Compile Status Failed ");
            break;
        }

        printf("%s | %s (%d)\n", infoLog, file, line);
    }

    return errorCode;
}

GLint glProgramCheckError_(GLuint program, GLenum pname ,const char *file, int line)
{
    GLint errorCode;
    glGetProgramiv(program, pname, &errorCode);
    if(!errorCode)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        switch(pname)
        {
            case GL_DELETE_STATUS:
                printf("Delete Status Failed");
            break;
            case GL_ATTACHED_SHADERS:
                printf("Attach Status Failed");
            break;
            case GL_LINK_STATUS:
                printf("Link Status Failed");
            break;
        }
        printf("%s | %s (%d)\n", infoLog, file, line);
    }

    return errorCode;
}