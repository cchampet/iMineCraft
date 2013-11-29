#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Cube.hpp"

namespace imac2gl3 {

    GLsizei Cube::insertPoint(GLsizei index, float texCoordsX, float texCoordsY, float posX, float posY, float posZ, float normalX, float normalY, float normalZ){
        ShapeVertex vertex;
        vertex.texCoords.x = texCoordsX; vertex.texCoords.y = texCoordsY;    
        vertex.position.x = posX; vertex.position.y = posY; vertex.position.z = posZ;    
        vertex.normal.x = normalX; vertex.normal.y = normalY; vertex.normal.z = normalZ;
        vertex.normal = glm::normalize(vertex.normal);

        m_pDataPointer[index] = vertex;
        ++index;
        return index;
    }

    void Cube::build(int type) {    
        std::vector<ShapeVertex> data;
        ShapeVertex vertex;

        type --;

        int nbTextureMax = 8; // nombre de type different max sur notre texture, a faire evoluer pour de la dynamique
        float division_1_sur_3 = 1/3.f;
        float portionParType = 1.f/(float)nbTextureMax;

        m_nVertexCount = 6 * 6; // 6 faces * 6 points (2 triangles)
        m_pDataPointer = new ShapeVertex[m_nVertexCount];
        

        GLsizei i = 0;
// FRONT
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     1, 0, 0,    0, 0, -1);
        i = insertPoint(i, division_1_sur_3, type*portionParType,       0, 0, 0,    0, 0, -1);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   0, 1, 0,    0, 0, -1);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   0, 1, 0,    0, 0, -1);
        i = insertPoint(i, 2*division_1_sur_3, (type+1)*portionParType, 1, 1, 0,    0, 0, -1);
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     1, 0, 0,    0, 0, -1);

// BOTTOM
        i = insertPoint(i, 1, type*portionParType,                      1, 0, 1,    0, -1, 0);
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     0, 0, 1,    0, -1, 0);
        i = insertPoint(i, 2*division_1_sur_3, (type+1)*portionParType, 0, 0, 0,    0, -1, 0);
        i = insertPoint(i, 2*division_1_sur_3, (type+1)*portionParType, 0, 0, 0,    0, -1, 0);
        i = insertPoint(i, 1, (type+1)*portionParType,                  1, 0, 0,    0, -1, 0);
        i = insertPoint(i, 1, type*portionParType,                      1, 0, 1,    0, -1, 0);

// BACK
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     0, 0, 1,    0, 0, 1);
        i = insertPoint(i, division_1_sur_3, type*portionParType,       1, 0, 1,    0, 0, 1);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   1, 1, 1,    0, 0, 1);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   1, 1, 1,    0, 0, 1);
        i = insertPoint(i, 2*division_1_sur_3, (type+1)*portionParType, 0, 1, 1,    0, 0, 1);
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     0, 0, 1,    0, 0, 1);

// TOP
        i = insertPoint(i, division_1_sur_3, type*portionParType,       1, 1, 0,    0, -1, 0);
        i = insertPoint(i, 0, type*portionParType,                      0, 1, 0,    0, -1, 0);
        i = insertPoint(i, 0, (type+1)*portionParType,                  0, 1, 1,    0, -1, 0);
        i = insertPoint(i, 0, (type+1)*portionParType,                  1, 1, 1,    0, -1, 0);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   1, 1, 1,    0, -1, 0);
        i = insertPoint(i, division_1_sur_3, type*portionParType,       0, 1, 0,    0, -1, 0);

// LEFT
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     0, 0, 0,    -1, 0, 0);
        i = insertPoint(i, division_1_sur_3, type*portionParType,       0, 0, 1,    -1, 0, 0);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   0, 1, 1,    -1, 0, 0);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   0, 1, 1,    -1, 0, 0);
        i = insertPoint(i, 2*division_1_sur_3, (type+1)*portionParType, 0, 1, 0,    -1, 0, 0);
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     0, 0, 0,    -1, 0, 0);

// RIGHT
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     1, 0, 1,    1, 0, 0);
        i = insertPoint(i, division_1_sur_3, type*portionParType,       1, 0, 0,    1, 0, 0);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   1, 1, 0,    1, 0, 0);
        i = insertPoint(i, division_1_sur_3, (type+1)*portionParType,   1, 1, 0,    1, 0, 0);
        i = insertPoint(i, 2*division_1_sur_3, (type+1)*portionParType, 1, 1, 1,    1, 0, 0);
        i = insertPoint(i, 2*division_1_sur_3, type*portionParType,     1, 0, 1,    1, 0, 0);
    }
}


