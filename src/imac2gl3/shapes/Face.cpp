#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Face.hpp"

namespace imac2gl3 {

    void Face::build(int position) {    
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


        m_nVertexCount = 6; // 6 points (2 triangles)
        m_pDataPointer = new ShapeVertex[m_nVertexCount];
        

        GLsizei i = 0;
        // FRONT
        m_pDataPointer[i] = data[0];i++;
        m_pDataPointer[i] = data[1];i++;
        m_pDataPointer[i] = data[2];i++;

        m_pDataPointer[i] = data[2];i++;
        m_pDataPointer[i] = data[3];i++;
        m_pDataPointer[i] = data[0];i++;
    }
}


