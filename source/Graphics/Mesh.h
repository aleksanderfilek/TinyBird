#ifndef TB_MESH_H_
#define TB_MESH_H_

#include<stdint.h>

typedef struct Mesh
{
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
    uint32_t indicesCount;
} Mesh;

Mesh* PlaneCreate();
void MeshDestroy(Mesh* mesh);
void MeshDraw(Mesh* mesh);

#endif