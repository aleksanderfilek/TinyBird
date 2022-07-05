#include"Mesh.h"

#include"../ThirdParty/GL/Gl.h"

#include<stdlib.h>

Mesh* PlaneCreate()
{
    float vertices[] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };
    float uvs[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };
    uint32_t indices[] = { 0, 1, 2, 1, 3, 2 };

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
    uint32_t indicesCount = 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), NULL, GL_STATIC_DRAW);  

    glBufferSubData(GL_ARRAY_BUFFER, 0, 8*sizeof(float), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, 8*sizeof(float), 8*sizeof(float), uvs);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)(8*sizeof(float)));

    glBindVertexArray(0);

    Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));

    mesh->VAO = VAO;
    mesh->VBO = VBO;
    mesh->EBO = EBO;
    mesh->indicesCount = indicesCount;

    return mesh;
}

void MeshDestroy(Mesh* mesh)
{
    glDeleteBuffers(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
}

void MeshDraw(Mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}