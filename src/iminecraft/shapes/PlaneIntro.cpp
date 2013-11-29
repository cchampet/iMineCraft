#include "iminecraft/shapes/PlaneIntro.hpp"
#include <omp.h>

namespace iminecraft {

    void PlaneIntro::insertPoint(float texCoordsX, float texCoordsY, float posX, float posY, float posZ, float normalX, float normalY, float normalZ){
        ShapeVertex vertex;
        vertex.texCoords.x = texCoordsX; vertex.texCoords.y = texCoordsY;    
        vertex.position.x = posX; vertex.position.y = posY; vertex.position.z = posZ;    
        vertex.normal.x = normalX; vertex.normal.y = normalY; vertex.normal.z = normalZ;

        temporaryVector.push_back(vertex);
        m_nVertexCount++;
    }

    void PlaneIntro::build(){       
        int m_width = 256;//land.getWidthMax();
        int m_height = 1;//land.getHeightMax();
        int m_deep = 256;//land.getDeepMax();

        int nbTextureMax = 8; // nombre de type different max sur notre texture, a faire evoluer pour de la dynamique

        float portionParType = 1.f/(float)nbTextureMax;
        float division_1_sur_3 = 1/3.f; // les divisions, ca coute cher alors autant le faire qu'une fois
        float division_2_sur_3 = 2*division_1_sur_3;

        m_nVertexCount = 0;

        for (int x = 0; x < m_width; ++x){
            for (int y = 0; y < m_height; ++y){
                for (int z = 0; z < m_deep; ++z){                       
                    insertPoint(division_1_sur_3, portionParType, x+1.0f, y, z, 0.f, 1.f, 0.f);
                    insertPoint(0.f, portionParType, x, y, z, 0.f, 1.f, 0.f);

                    insertPoint(0.f, 0.f, x, y, z+1.f, 0.f, 1.f, 0.f);
                    insertPoint(0.f, 0.f, x, y, z+1.f, 0.f, 1.f, 0.f);

                    insertPoint(division_1_sur_3, 0.f, x+1.f, y, z+1.0f, 0.f, 1.f, 0.f);
                    insertPoint(division_1_sur_3, portionParType, x+1.f, y, z, 0.f, 1.f, 0.f);
                }
            }
        }


        m_pDataPointer = new ShapeVertex[m_nVertexCount];

        for (int i = 0; i < m_nVertexCount; ++i){
            m_pDataPointer[i] = temporaryVector.at(i);
        }

        temporaryVector.clear();
    }
}


