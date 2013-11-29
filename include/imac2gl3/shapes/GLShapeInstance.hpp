#ifndef _IMAC2GL3_GLSHAPEINSTANCE_HPP_
#define _IMAC2GL3_GLSHAPEINSTANCE_HPP_

#include "Sphere.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Cube.hpp"
#include "NeutralCube.hpp"
#include "imac2gl3/shapes/MonsterCube.hpp"
#include "Face.hpp"
#include "Skybox.hpp"
#include "iminecraft/shapes/MeshChunk.hpp"
#include "iminecraft/shapes/PlaneIntro.hpp"

#include <GL/glew.h>

#include "../shader_tools.hpp"
#include "common.hpp"

#define POSITION_LOCATION 0
#define NORMAL_LOCATION 1
#define TEXCOORDS_LOCATION 2


namespace imac2gl3 {

	class GLShapeInstance{
	    public:
		    GLShapeInstance(const imac2gl3::Sphere & sphere); // Constructeur
		    GLShapeInstance(const imac2gl3::Cone & cone);
		    GLShapeInstance(const imac2gl3::Cylinder & cylinder);
		    GLShapeInstance(const imac2gl3::Cube & cube);
		    GLShapeInstance(const iminecraft::MeshChunk & meshChunk);
		    GLShapeInstance(const imac2gl3::Face & face);
		    GLShapeInstance(const imac2gl3::Skybox & skybox);
		    GLShapeInstance(const imac2gl3::NeutralCube & cube);
		    GLShapeInstance(const imac2gl3::MonsterCube & cube);
		    GLShapeInstance(const iminecraft::PlaneIntro & planeIntro);
			~GLShapeInstance(); // Destructeur

			GLuint getVbo(){ return vbo; };
		    GLuint getVao(){ return vao; };

			void createVbo(GLsizeiptr byteSize, const GLvoid* dataPointer);
			void createVao(GLint PositionNumComponents, GLenum DataType, GLsizei VertexByteSize, const GLvoid* PositionOffset, GLint NormalNumComponents, const GLvoid* NormalOffset, GLint TexCoordsNumComponents, const GLvoid* TexCoordsOffset);

		    void draw();

		    int getXPosition(){ return xPosition;};
		    int getZPosition(){ return zPosition;};
		    void setXPosition(int x){ xPosition = x;};
		    void setZPosition(int z){ zPosition = z;};

	    private:
	    	int xPosition;
	    	int zPosition;

	    	GLuint vao;
		    GLfloat vertexCount;    	
		    GLuint vbo;
	};

}

#endif
