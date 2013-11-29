#include "iminecraft/shapes/MeshChunk.hpp"
#include <omp.h>

namespace iminecraft {

    void MeshChunk::insertPoint(float texCoordsX, float texCoordsY, float posX, float posY, float posZ, float normalX, float normalY, float normalZ){
        ShapeVertex vertex;
        vertex.texCoords.x = texCoordsX; vertex.texCoords.y = texCoordsY;    
        vertex.position.x = posX; vertex.position.y = posY; vertex.position.z = posZ;    
        vertex.normal.x = normalX; vertex.normal.y = normalY; vertex.normal.z = normalZ;

        temporaryVector.push_back(vertex);
        m_nVertexCount++;
    }


    int MeshChunk::getVal(unsigned int x, unsigned int y, unsigned int z) {
        if(x>=0 && x < M_WIDTH && y>=0 && y<M_HEIGHT && z>=0 && z<M_DEEP)
            return cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType();
        else if(y<=0)
                return 0; // top limit of the chunk
        else
            return -1; //wrong chunk
    }

    bool MeshChunk::getVisible(unsigned int x, unsigned int y, unsigned int z) {
        // if(getVal(x+1, y, z) > 1 && getVal(x-1, y, z) > 1
        //                         && getVal(x, y, z+1) > 1
        //                         && getVal(x, y, z-1) > 1
        //                         && getVal(x, y+1, z) > 1
        //                         && getVal(x, y-1, z) > 1){
        if(getVal(x+1, y, z) > 0 && getVal(x-1, y, z) > 0
                                && getVal(x, y, z+1) > 0
                                && getVal(x, y, z-1) > 0
                                && getVal(x, y+1, z) > 0
                                && getVal(x, y-1, z) > 0){
            return false;
            // tout autour n'est pas de l'air : on est pas visible (faux si c'est de l'eau mais bon)
        }
        return true;
    }

    bool MeshChunk::checkFaceVisibility_top(int x, int y, int z){ 
        // top
        if(getVal(x,y+1,z) > 0) // il y a un cube  //1) // il y a un cube et pas de l'eau
            return false;
        return true;
    }
    bool MeshChunk::checkFaceVisibility_bottom(int x, int y, int z){ 
        // bottom
        if(getVal(x,y-1,z) > 0) // il y a un cube  //1) // il y a un cube et pas de l'eau
            return false;
        return true;
    }
    bool MeshChunk::checkFaceVisibility_left(int x, int y, int z){
        // left
        if(getVal(x-1,y,z) > 0) // il y a un cube  //1) // il y a un cube et pas de l'eau
            return false;
        return true;
    }
    bool MeshChunk::checkFaceVisibility_right(int x, int y, int z){
        // right
        if(getVal(x+1,y,z) > 0) // il y a un cube  //1) // il y a un cube et pas de l'eau
            return false;
        return true;
    }
    bool MeshChunk::checkFaceVisibility_back(int x, int y, int z){
        // back
        if(getVal(x,y,z+1) > 0) // il y a un cube  //1) // il y a un cube et pas de l'eau
            return false;
        return true;
    }
    bool MeshChunk::checkFaceVisibility_front(int x, int y, int z){
        // front
        if(getVal(x,y,z-1) > 0) // il y a un cube  //1) // il y a un cube et pas de l'eau
            return false;
        return true;
    }

    void MeshChunk::InsertWater(int x, int y, int z, float portionParType){
        float portionOfBlockInTexture_Y = 0.f;
        float portionOfBlockInTexture_Y_PLUSONE = portionParType;
        // TOP
        if(getVal(x,y+1,z) == 0){
            insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.0f, y+1.0f, z, 0.f, 1.f, 0.f);
            insertPoint(0.f, portionOfBlockInTexture_Y_PLUSONE, x, y+1.0f, z, 0.f, 1.f, 0.f);

            insertPoint(0.f, portionOfBlockInTexture_Y, x, y+1.0f, z+1.0f, 0.f, 1.f, 0.f);
            insertPoint(0.f, portionOfBlockInTexture_Y, x, y+1.0f, z+1.0f, 0.f, 1.f, 0.f);

            insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.0f, 0.f, 1.f, 0.f);
            insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y+1.0f, z, 0.f, 1.f, 0.f);
        }
        // BOTTOM
        if(getVal(x,y-1,z) == 0){        
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.0f, y, z+1.0f, 0.f, -1.f, 0.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.0f, 0.f, -1.f, 0.f);

            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y, z, 0.f, -1.f, 0.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y, z, 0.f, -1.f, 0.f);

            insertPoint(1, portionOfBlockInTexture_Y, x+1.f, y, z, 0.f, -1.f, 0.f);
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 0.f, -1.f, 0.f);
        }
        // LEFT
        if(getVal(x-1,y,z) == 0){
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z, -1.f, 0.f, 0.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, -1.f, 0.f, 0.f);

            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, -1.f, 0.f, 0.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, -1.f, 0.f, 0.f);

            insertPoint(1, portionOfBlockInTexture_Y, x, y+1.f, z, -1.f, 0.f, 0.f);
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z, -1.f, 0.f, 0.f);
        }
        // RIGHT
        if(getVal(x+1,y,z) == 0){
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 1.f, 0.f, 0.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 1.f, 0.f, 0.f);

            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 1.f, 0.f, 0.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 1.f, 0.f, 0.f);

            insertPoint(1, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 1.f, 0.f, 0.f);
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 1.f, 0.f, 0.f);
        }
        // BACK
        if(getVal(x,y,z+1) == 0){
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, 0.f, 0.f, 1.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 0.f, 0.f, 1.f);

            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 0.f, 0.f, 1.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 0.f, 0.f, 1.f);

            insertPoint(1, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, 0.f, 0.f, 1.f);
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, 0.f, 0.f, 1.f);
        }
        // FRONT
        if(getVal(x,y+1,z) == 0){
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 0.f, 0.f, -1.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z, 0.f, 0.f, -1.f);

            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, 0.f, 0.f, -1.f);
            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, 0.f, 0.f, -1.f);

            insertPoint(1, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 0.f, 0.f, -1.f);
            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 0.f, 0.f, -1.f);
        }
    }

    void MeshChunk::build(){       
        int m_width = 16;//land.getWidthMax();
        int m_height = 128;//land.getHeightMax();
        int m_deep = 16;//land.getDeepMax();

        int nbTextureMax = 8; // nombre de type different max sur notre texture, a faire evoluer pour de la dynamique

        float portionParType = 1.f/(float)nbTextureMax;

        m_nVertexCount = 0;

        for (int x = 0; x < m_width; ++x){
            for (int y = 0; y < m_height; ++y){
                for (int z = 0; z < m_deep; ++z){
                    if(getVal(x,y,z) > 0 && getVisible(x,y,z) > 0){
                        int typeOfBlock = getVal(x,y,z) - 1;
                        float portionOfBlockInTexture_Y = typeOfBlock*portionParType;
                        float portionOfBlockInTexture_Y_PLUSONE = portionOfBlockInTexture_Y+portionParType;

                        bool visibilityTop = checkFaceVisibility_top(x, y, z);
                        if(visibilityTop){
                            // TOP
                            insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.0f, y+1.0f, z, 0.f, 1.f, 0.f);
                            insertPoint(0.f, portionOfBlockInTexture_Y_PLUSONE, x, y+1.0f, z, 0.f, 1.f, 0.f);

                            insertPoint(0.f, portionOfBlockInTexture_Y, x, y+1.0f, z+1.0f, 0.f, 1.f, 0.f);
                            insertPoint(0.f, portionOfBlockInTexture_Y, x, y+1.0f, z+1.0f, 0.f, 1.f, 0.f);

                            insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.0f, 0.f, 1.f, 0.f);
                            insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y+1.0f, z, 0.f, 1.f, 0.f);
                        }
                        if(checkFaceVisibility_bottom(x, y, z)){
                        // BOTTOM
                            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.0f, y, z+1.0f, 0.f, -1.f, 0.f);
                            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.0f, 0.f, -1.f, 0.f);

                            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y, z, 0.f, -1.f, 0.f);
                            insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y, z, 0.f, -1.f, 0.f);

                            insertPoint(1, portionOfBlockInTexture_Y, x+1.f, y, z, 0.f, -1.f, 0.f);
                            insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 0.f, -1.f, 0.f);
                        }
                        if(checkFaceVisibility_left(x, y, z)){
                            // LEFT
                            if(!visibilityTop && getVal(x,y,z) == 4){
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z, -1.f, 0.f, 0.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, -1.f, 0.f, 0.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, -1.f, 0.f, 0.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, -1.f, 0.f, 0.f);

                                insertPoint(1, portionOfBlockInTexture_Y, x, y+1.f, z, -1.f, 0.f, 0.f);
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z, -1.f, 0.f, 0.f);
                            }else{
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z, -1.f, 0.f, 0.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, -1.f, 0.f, 0.f);

                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, -1.f, 0.f, 0.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, -1.f, 0.f, 0.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, -1.f, 0.f, 0.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z, -1.f, 0.f, 0.f);
                            }
                        }
                        if(checkFaceVisibility_right(x, y, z)){
                            // RIGHT
                            if(!visibilityTop && getVal(x,y,z) == 4){
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 1.f, 0.f, 0.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 1.f, 0.f, 0.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 1.f, 0.f, 0.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 1.f, 0.f, 0.f);

                                insertPoint(1, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 1.f, 0.f, 0.f);
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 1.f, 0.f, 0.f);
                            }else{
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 1.f, 0.f, 0.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 1.f, 0.f, 0.f);

                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 1.f, 0.f, 0.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 1.f, 0.f, 0.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 1.f, 0.f, 0.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 1.f, 0.f, 0.f);
                            }
                        }
                        if(checkFaceVisibility_back(x, y, z)){
                            // BACK
                            if(!visibilityTop && getVal(x,y,z) == 4){
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, 0.f, 0.f, 1.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 0.f, 0.f, 1.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 0.f, 0.f, 1.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 0.f, 0.f, 1.f);

                                insertPoint(1, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, 0.f, 0.f, 1.f);
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, 0.f, 0.f, 1.f);
                            }else{
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, 0.f, 0.f, 1.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z+1.f, 0.f, 0.f, 1.f);

                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 0.f, 0.f, 1.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z+1.f, 0.f, 0.f, 1.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z+1.f, 0.f, 0.f, 1.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z+1.f, 0.f, 0.f, 1.f);
                            }
                        }
                        if(checkFaceVisibility_front(x, y, z)){
                            // FRONT
                            if(!visibilityTop && getVal(x,y,z) == 4){
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 0.f, 0.f, -1.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z, 0.f, 0.f, -1.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, 0.f, 0.f, -1.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, 0.f, 0.f, -1.f);

                                insertPoint(1, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 0.f, 0.f, -1.f);
                                insertPoint(1, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 0.f, 0.f, -1.f);
                            }else{
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 0.f, 0.f, -1.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y_PLUSONE, x, y, z, 0.f, 0.f, -1.f);

                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, 0.f, 0.f, -1.f);
                                insertPoint(division_1_sur_3, portionOfBlockInTexture_Y, x, y+1.f, z, 0.f, 0.f, -1.f);

                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y, x+1.f, y+1.f, z, 0.f, 0.f, -1.f);
                                insertPoint(division_2_sur_3, portionOfBlockInTexture_Y_PLUSONE, x+1.f, y, z, 0.f, 0.f, -1.f);
                            }
                        }
                    }//else if(getVal(x,y,z) == 1){
                    //     InsertWater(x, y, z, portionParType);
                    // }
                }
            }
        }


        m_pDataPointer = new ShapeVertex[m_nVertexCount];

        for (int i = 0; i < m_nVertexCount; ++i){
            m_pDataPointer[i] = temporaryVector.at(i);
        }

        temporaryVector.clear();
        cubeDataVector.clear();
    }
}


