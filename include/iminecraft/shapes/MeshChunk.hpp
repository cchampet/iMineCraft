#ifndef __IMINECRAFT__MESHCHUNK_HPP_
#define __IMINECRAFT__MESHCHUNK_HPP_

#include <GL/glew.h>

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "imac2gl3/shapes/common.hpp"
#include "iminecraft/land/CubeData.hpp"


using namespace std;
using namespace imac2gl3;


#define M_WIDTH     16
#define M_HEIGHT    128
#define M_DEEP      16

namespace iminecraft {

    class MeshChunk {

        vector<iminecraft::CubeData> cubeDataVector;


        static const GLint POSITION_NUM_COMPONENTS = 3;
        static const GLint NORMAL_NUM_COMPONENTS = 3;
        static const GLint TEXCOORDS_NUM_COMPONENTS = 2;
        
        static const GLsizei POSITION_OFFSET = 0;
        static const GLsizei NORMAL_OFFSET = POSITION_NUM_COMPONENTS * sizeof(GLfloat);
        static const GLsizei TEX_COORDS_OFFSET = (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS) * sizeof(GLfloat);
        
        static const GLsizei VERTEX_BYTE_SIZE = 
            (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS + TEXCOORDS_NUM_COMPONENTS) * sizeof(GLfloat);
            
        // Alloue et construit les données (implantation dans le .cpp)
        void build();

        int getVal(unsigned int x, unsigned int y, unsigned int z);
        bool getVisible(unsigned int x, unsigned int y, unsigned int z);
        bool checkFaceVisibility_top(int x, int y, int z);
        bool checkFaceVisibility_bottom(int x, int y, int z);
        bool checkFaceVisibility_left(int x, int y, int z);
        bool checkFaceVisibility_right(int x, int y, int z);
        bool checkFaceVisibility_back(int x, int y, int z);
        bool checkFaceVisibility_front(int x, int y, int z);

        vector<ShapeVertex> temporaryVector;
        
        // Pas de copie possible
        MeshChunk(const MeshChunk& c) {
        }
        
        MeshChunk& operator =(const MeshChunk& c) {
            return *this;
        }

        float division_1_sur_3; // les divisions, ca coute cher alors autant le faire qu'une fois
        float division_2_sur_3;

        void InsertWater(int x, int y, int z, float portionParType);
        void insertPoint(float texCoordsX, float texCoordsY, float posX, float posY, float posZ, float normalX, float normalY, float normalZ);
    public:
        // Constructeur: alloue le tableau de données et construit les attributs des vertex
        MeshChunk(vector<iminecraft::CubeData> _cubeDataVector):
            m_pDataPointer(0), m_nVertexCount(0) {
            cubeDataVector = _cubeDataVector;
            division_1_sur_3 = 1/3.f;
            division_2_sur_3 = 2/3.f;
            build(); // Construction (voir le .cpp)
        }
        
        // Destructeur: désalloue le tableau de données
        ~MeshChunk() {
            delete [] m_pDataPointer;
        }

        // Renvoit le pointeur vers les données
        const GLvoid* getDataPointer() const {
            return m_pDataPointer;
        }
        
        // Renvoit le nombre de vertex
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

        // Renvoit la taille du tableau en octets
        GLsizeiptr getByteSize() const {
            return getVertexCount() * VERTEX_BYTE_SIZE; // Nombre de sommet * taille d'un sommet
        }
        
        // Renvoit le nombre de composantes de l'attribut position
        GLint getPositionNumComponents() const {
            return POSITION_NUM_COMPONENTS;
        }
        
        // Renvoit le nombre de composantes de l'attribut normale
        GLint getNormalNumComponents() const {
            return NORMAL_NUM_COMPONENTS;
        }
        
        // Renvoit le nombre de composantes de l'attribut coordonnées de texture
        GLint getTexCoordsNumComponents() const {
            return TEXCOORDS_NUM_COMPONENTS;
        }
        
        // Renvoit la taille d'un vertex en octets
        GLsizei getVertexByteSize() const {
            return VERTEX_BYTE_SIZE;
        }
        
        // Renvoit l'offset de l'attribut position
        const GLvoid* getPositionOffset() const {
            return reinterpret_cast<const GLvoid*>(POSITION_OFFSET);
        }
        
        // Renvoit l'offset de l'attribut normale
        const GLvoid* getNormalOffset() const {
            return reinterpret_cast<const GLvoid*>(NORMAL_OFFSET);
        }
        
        // Renvoit l'offset de l'attribut coordonnées de texture
        const GLvoid* getTexCoordsOffset() const {
            return reinterpret_cast<const GLvoid*>(TEX_COORDS_OFFSET);
        }
        
        // Renvoit le type OpenGL d'une composante d'attribut
        GLenum getDataType() const {
            return GL_FLOAT;
        }

    private:
        ShapeVertex* m_pDataPointer; // Pointeur vers les données du tableau
        GLsizei m_nVertexCount; // Nombre de sommets
    };
}

#endif
