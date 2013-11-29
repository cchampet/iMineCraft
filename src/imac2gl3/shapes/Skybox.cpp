#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Skybox.hpp"

namespace imac2gl3 {

    GLsizei Skybox::insertPoint(ShapeVertex data, GLsizei index, float texCoordsX, float texCoordsY, float posX, float posY, float posZ, float normalX, float normalY, float normalZ){
        m_pDataPointer[index] = data;
        m_pDataPointer[index].texCoords.x = texCoordsX;m_pDataPointer[index].texCoords.y = texCoordsY;
        m_pDataPointer[index].position.x = posX;m_pDataPointer[index].position.y = posY;m_pDataPointer[index].position.z = posZ;
        m_pDataPointer[index].normal.x = normalX;m_pDataPointer[index].normal.y = normalY;m_pDataPointer[index].normal.z = normalZ;
        ++index;
        return index;
    }


    void Skybox::build(GLfloat height) {    
        std::vector<ShapeVertex> data;

        ShapeVertex vertex;    

// FRONT BOTTOM
// 1,0,0
        vertex.texCoords.x = 1.f;
        vertex.texCoords.y = 0.f;    
        vertex.position.x = 1.f;
        vertex.position.y = 0.f;
        vertex.position.z = 0.f;    
        vertex.normal.x = 1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// 0,0,0
        vertex.texCoords.x = 0.f;
        vertex.texCoords.y = 0.f;    
        vertex.position.x = 0.f;
        vertex.position.y = 0.f;
        vertex.position.z = 0.f;    
        vertex.normal.x = -1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// FRONT UP
// 0,1,0
        vertex.texCoords.x = 0.f;
        vertex.texCoords.y = 1.f;    
        vertex.position.x = 0.f;
        vertex.position.y = 1.f;
        vertex.position.z = 0.f;    
        vertex.normal.x = -1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);
// 1,1,0
        vertex.texCoords.x = 1.f;
        vertex.texCoords.y = 1.f;    
        vertex.position.x = 1.f;
        vertex.position.y = 1.f;
        vertex.position.z = 0.f;    
        vertex.normal.x = 1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// BACK BOTTOM
// 1,0,1
        vertex.texCoords.x = 1.f;
        vertex.texCoords.y = 1.f;    
        vertex.position.x = 1.f;
        vertex.position.y = 0.f;
        vertex.position.z = 1.f;
        vertex.normal.x = 1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// 0,0,1
        vertex.texCoords.x = 0.f;
        vertex.texCoords.y = 1.f;    
        vertex.position.x = 0.f;
        vertex.position.y = 0.f;
        vertex.position.z = 1.f;    
        vertex.normal.x = -1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// BACK UP
// 0,1,1
        vertex.texCoords.x = 0.f;
        vertex.texCoords.y = 0.f;    
        vertex.position.x = 0.f;
        vertex.position.y = 1.f;
        vertex.position.z = 1.f;    
        vertex.normal.x = -1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);
// 1,1,1
        vertex.texCoords.x = 1.f;
        vertex.texCoords.y = 0.f;    
        vertex.position.x = 1.f;
        vertex.position.y = 1.f;
        vertex.position.z = 1.f;    
        vertex.normal.x = 1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);




        m_nVertexCount = 6 * 6; // 6 faces * 6 points (2 triangles)
        m_pDataPointer = new ShapeVertex[m_nVertexCount];
        
        GLsizei i = 0;
// FRONT
        i = insertPoint(data[0], i, 0.25f, 2/3.f,   0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f);
        i = insertPoint(data[1], i, 0.f, 2/3.f,     -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f);

        i = insertPoint(data[2], i, 0.f, 1/3.f,     -0.5f, 0.5f, -0.5f, 0.f, 0.f, -1.f);
        i = insertPoint(data[2], i, 0.f, 1/3.f,     -0.5f, 0.5f, -0.5f, 0.f, 0.f, -1.f);

        i = insertPoint(data[3], i, 0.25f, 1/3.f,   0.5f, 0.5f, -0.5f, 0.f, 0.f, -1.f);
        i = insertPoint(data[0], i, 0.25f, 2/3.f,   0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f);

// BOTTOM
        i = insertPoint(data[4], i, 0.5f, 1.f,     0.5f, -0.5f, 0.5f, 0.f, -1.f, 0.f);
        i = insertPoint(data[5], i, 0.25f, 1.f,      -0.5f, -0.5f, 0.5f, 0.f, -1.f, 0.f);

        i = insertPoint(data[1], i, 0.25f, 0.67f,    -0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f);
        i = insertPoint(data[1], i, 0.25f, 0.67f,    -0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f);

        i = insertPoint(data[0], i, 0.5f, 0.67f,   0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f);
        i = insertPoint(data[4], i, 0.5f, 1.f,     0.5f, -0.5f, 0.5f, 0.f, -1.f, 0.f);

// BACK
        i = insertPoint(data[7], i, 0.75f, 2/3.f,    -0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f);
        i = insertPoint(data[6], i, 0.5f, 2/3.f,   0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f);

        i = insertPoint(data[5], i, 0.5f, 1/3.f,   0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f);
        i = insertPoint(data[5], i, 0.5f, 1/3.f,   0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f);

        i = insertPoint(data[4], i, 0.75f, 1/3.f,    -0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f);
        i = insertPoint(data[7], i, 0.75f, 2/3.f,    -0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f);

// TOP
        i = insertPoint(data[3], i, 0.5f, 1/3.f,   0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f);
        i = insertPoint(data[2], i, 0.25f, 1/3.f,    0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f);

        i = insertPoint(data[6], i, 0.25f, 0.f,      -0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f);
        i = insertPoint(data[6], i, 0.25f, 0.f,      -0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f);

        i = insertPoint(data[7], i, 0.5f, 0.f,     -0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f);
        i = insertPoint(data[3], i, 0.5f, 1/3.f,   0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f);

// LEFT
        i = insertPoint(data[1], i, 1.f, 2/3.f,   -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f);
        i = insertPoint(data[5], i, 0.75f, 2/3.f,    -0.5f, -0.5f, 0.5f, -1.f, 0.f, 0.f);

        i = insertPoint(data[6], i, 0.75f, 1/3.f,    -0.5f, 0.5f, 0.5f, -1.f, 0.f, 0.f);
        i = insertPoint(data[6], i, 0.75f, 1/3.f,    -0.5f, 0.5f, 0.5f, -1.f, 0.f, 0.f);

        i = insertPoint(data[2], i, 1.f, 1/3.f,   -0.5f, 0.5f, -0.5f, -1.f, 0.f, 0.f);
        i = insertPoint(data[1], i, 1.f, 2/3.f,   -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f);

// RIGHT
        i = insertPoint(data[4], i, 0.5f, 2/3.f,     0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f);
        i = insertPoint(data[0], i, 0.25f, 2/3.f,   0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f);

        i = insertPoint(data[3], i, 0.25f, 1/3.f,   0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f);
        i = insertPoint(data[3], i, 0.25f, 1/3.f,   0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f);

        i = insertPoint(data[7], i, 0.5f, 1/3.f,     0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f);
        i = insertPoint(data[4], i, 0.5f, 2/3.f,     0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f);
         
        // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
        // par un Index Buffer Object, que nous verrons dans les prochains TDs
    }
}


