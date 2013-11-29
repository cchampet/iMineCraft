#include <cmath>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/NeutralCube.hpp"

namespace imac2gl3 {

    void NeutralCube::build(int type) {    
        std::vector<ShapeVertex> data;
        ShapeVertex vertex;

        type --;

        int nbTextureMax = 4; // nombre de type different max sur notre texture, a faire evoluer pour de la dynamique
        float division_1_sur_3 = 1/3.f;
        float portionParType = 1.f/(float)nbTextureMax;

// FRONT BOTTOM
// 1,0,0
        vertex.texCoords.x = 2*division_1_sur_3;
        vertex.texCoords.y = (type+1)*portionParType;    
        vertex.position.x = 0.5f;
        vertex.position.y = 0.f;
        vertex.position.z = -0.5f;
        vertex.normal.x = 1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// 0,0,0
        vertex.texCoords.x = division_1_sur_3;
        vertex.texCoords.y = (type+1)*portionParType;    
        vertex.position.x = -0.5f;
        vertex.position.y = 0.f;
        vertex.position.z = -0.5f;
        vertex.normal.x = -1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// FRONT UP
// 0,1,0
        vertex.texCoords.x = division_1_sur_3;
        vertex.texCoords.y = type*portionParType;    
        vertex.position.x = -0.5f;
        vertex.position.y = 1.f;
        vertex.position.z = -0.5f;
        vertex.normal.x = -1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);
// 1,1,0
        vertex.texCoords.x = 2*division_1_sur_3;
        vertex.texCoords.y = type*portionParType;    
        vertex.position.x = 0.5f;
        vertex.position.y = 1.f;
        vertex.position.z = -0.5f;
        vertex.normal.x = 1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = 1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// BACK BOTTOM
// 1,0,1
        vertex.texCoords.x = 1.f;
        vertex.texCoords.y = 1.f;    
        vertex.position.x = 0.5f;
        vertex.position.y = 0.f;
        vertex.position.z = 0.5f;
        vertex.normal.x = 1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// 0,0,1
        vertex.texCoords.x = 0.f;
        vertex.texCoords.y = 1.f;    
        vertex.position.x = -0.5f;
        vertex.position.y = 0.f;
        vertex.position.z = 0.5f;
        vertex.normal.x = -1.f;
        vertex.normal.y = -1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);

// BACK UP
// 0,1,1
        vertex.texCoords.x = 0.f;
        vertex.texCoords.y = 0.f;    
        vertex.position.x = -0.5f;
        vertex.position.y = 1.f;
        vertex.position.z = 0.5f;
        vertex.normal.x = -1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);
// 1,1,1
        vertex.texCoords.x = 1.f;
        vertex.texCoords.y = 0.f;    
        vertex.position.x = 0.5f;
        vertex.position.y = 1.f;
        vertex.position.z = 0.5f;
        vertex.normal.x = 1.f;
        vertex.normal.y = 1.f;
        vertex.normal.z = -1.f;
        vertex.normal = glm::normalize(vertex.normal);    
        data.push_back(vertex);




        m_nVertexCount = 6 * 6; // 6 faces * 6 points (2 triangles)
        m_pDataPointer = new ShapeVertex[m_nVertexCount];
        

        GLsizei i = 0;
// FRONT
        m_pDataPointer[i] = data[5];m_pDataPointer[i].texCoords.x = 2*division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[4];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[7];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;

        m_pDataPointer[i] = data[7];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[6];m_pDataPointer[i].texCoords.x = 2*division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[5];m_pDataPointer[i].texCoords.x = 2*division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;

// BOTTOM
        m_pDataPointer[i] = data[4];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[5];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[1];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;

        m_pDataPointer[i] = data[1];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[0];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[4];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;

// BACK
        m_pDataPointer[i] = data[0];m_pDataPointer[i].texCoords.x = 1;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[1];m_pDataPointer[i].texCoords.x = 2*division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[2];m_pDataPointer[i].texCoords.x = 2*division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;

        m_pDataPointer[i] = data[2];m_pDataPointer[i].texCoords.x = 2*division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[3];m_pDataPointer[i].texCoords.x = 1;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[0];m_pDataPointer[i].texCoords.x = 1;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;

// TOP
        m_pDataPointer[i] = data[3];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[2];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[6];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;

        m_pDataPointer[i] = data[6];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[7];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[3];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;

// LEFT
        m_pDataPointer[i] = data[1];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[5];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[6];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;

        m_pDataPointer[i] = data[6];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[2];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[1];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;

// RIGHT
        m_pDataPointer[i] = data[4];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[0];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;
        m_pDataPointer[i] = data[3];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;

        m_pDataPointer[i] = data[3];m_pDataPointer[i].texCoords.x = 0;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[7];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = type*portionParType;
        i++;
        m_pDataPointer[i] = data[4];m_pDataPointer[i].texCoords.x = division_1_sur_3;m_pDataPointer[i].texCoords.y = (type+1)*portionParType;
        i++;

         
        // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
        // par un Index Buffer Object, que nous verrons dans les prochains TDs
    }
}


