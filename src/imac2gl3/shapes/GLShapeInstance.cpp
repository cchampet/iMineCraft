#include "imac2gl3/shapes/GLShapeInstance.hpp"


namespace imac2gl3 {

	// Constructeur
	GLShapeInstance::GLShapeInstance(const imac2gl3::Sphere & mySphere){
	    vertexCount = mySphere.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(mySphere.getByteSize(), mySphere.getDataPointer());
	    createVao(mySphere.getPositionNumComponents(), mySphere.getDataType(), mySphere.getVertexByteSize(), mySphere.getPositionOffset(), mySphere.getNormalNumComponents(), mySphere.getNormalOffset(), mySphere.getTexCoordsNumComponents(), mySphere.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::Cone & cone){
	    vertexCount = cone.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(cone.getByteSize(), cone.getDataPointer());
	    createVao(cone.getPositionNumComponents(), cone.getDataType(), cone.getVertexByteSize(), cone.getPositionOffset(), cone.getNormalNumComponents(), cone.getNormalOffset(), cone.getTexCoordsNumComponents(), cone.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::Cylinder & cylinder){
	    vertexCount = cylinder.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(cylinder.getByteSize(), cylinder.getDataPointer());
	    createVao(cylinder.getPositionNumComponents(), cylinder.getDataType(), cylinder.getVertexByteSize(), cylinder.getPositionOffset(), cylinder.getNormalNumComponents(), cylinder.getNormalOffset(), cylinder.getTexCoordsNumComponents(), cylinder.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::Cube & cube){
	    vertexCount = cube.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(cube.getByteSize(), cube.getDataPointer());
	    createVao(cube.getPositionNumComponents(), cube.getDataType(), cube.getVertexByteSize(), cube.getPositionOffset(), cube.getNormalNumComponents(), cube.getNormalOffset(), cube.getTexCoordsNumComponents(), cube.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::NeutralCube & cube){
	    vertexCount = cube.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(cube.getByteSize(), cube.getDataPointer());
	    createVao(cube.getPositionNumComponents(), cube.getDataType(), cube.getVertexByteSize(), cube.getPositionOffset(), cube.getNormalNumComponents(), cube.getNormalOffset(), cube.getTexCoordsNumComponents(), cube.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::MonsterCube & cube){
	    vertexCount = cube.getVertexCount();
	    vbo = 0;
	    vao = 0;
	    createVbo(cube.getByteSize(), cube.getDataPointer());
	    createVao(cube.getPositionNumComponents(), cube.getDataType(), cube.getVertexByteSize(), cube.getPositionOffset(), cube.getNormalNumComponents(), cube.getNormalOffset(), cube.getTexCoordsNumComponents(), cube.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const iminecraft::MeshChunk & meshChunk){
	    vertexCount = meshChunk.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(meshChunk.getByteSize(), meshChunk.getDataPointer());
	    createVao(meshChunk.getPositionNumComponents(), meshChunk.getDataType(), meshChunk.getVertexByteSize(), meshChunk.getPositionOffset(), meshChunk.getNormalNumComponents(), meshChunk.getNormalOffset(), meshChunk.getTexCoordsNumComponents(), meshChunk.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::Face & face){
	    vertexCount = face.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(face.getByteSize(), face.getDataPointer());
	    createVao(face.getPositionNumComponents(), face.getDataType(), face.getVertexByteSize(), face.getPositionOffset(), face.getNormalNumComponents(), face.getNormalOffset(), face.getTexCoordsNumComponents(), face.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const imac2gl3::Skybox & skybox){
	    vertexCount = skybox.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(skybox.getByteSize(), skybox.getDataPointer());
	    createVao(skybox.getPositionNumComponents(), skybox.getDataType(), skybox.getVertexByteSize(), skybox.getPositionOffset(), skybox.getNormalNumComponents(), skybox.getNormalOffset(), skybox.getTexCoordsNumComponents(), skybox.getTexCoordsOffset());
	}

	GLShapeInstance::GLShapeInstance(const iminecraft::PlaneIntro & planeIntro){
	    vertexCount = planeIntro.getVertexCount();
	    vbo = 0;
	    vao = 0;    
	    createVbo(planeIntro.getByteSize(), planeIntro.getDataPointer());
	    createVao(planeIntro.getPositionNumComponents(), planeIntro.getDataType(), planeIntro.getVertexByteSize(), planeIntro.getPositionOffset(), planeIntro.getNormalNumComponents(), planeIntro.getNormalOffset(), planeIntro.getTexCoordsNumComponents(), planeIntro.getTexCoordsOffset());
	}

	void GLShapeInstance::createVao(GLint PositionNumComponents, GLenum DataType, GLsizei VertexByteSize, const GLvoid* PositionOffset, GLint NormalNumComponents, const GLvoid* NormalOffset, GLint TexCoordsNumComponents, const GLvoid* TexCoordsOffset){
	    glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);
			glEnableVertexAttribArray(POSITION_LOCATION);
			glEnableVertexAttribArray(NORMAL_LOCATION);
			glEnableVertexAttribArray(TEXCOORDS_LOCATION);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			    glVertexAttribPointer(POSITION_LOCATION,
			                        PositionNumComponents,
			                        DataType,
			                        GL_FALSE,
			                        VertexByteSize,
			                        PositionOffset);
			    glVertexAttribPointer(NORMAL_LOCATION,
			                        NormalNumComponents,
			                        DataType,
			                        GL_FALSE,
			                        VertexByteSize,
			                        NormalOffset);
			    glVertexAttribPointer(TEXCOORDS_LOCATION,
			                        TexCoordsNumComponents,
			                        DataType,
			                        GL_FALSE,
			                        VertexByteSize,
			                        TexCoordsOffset);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
	    glBindVertexArray(0);
	}

	void GLShapeInstance::createVbo(GLsizeiptr byteSize, const GLvoid* dataPointer){
	    glGenBuffers(1, &vbo);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, byteSize, dataPointer, GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLShapeInstance::draw(){
	    glBindVertexArray(vao);
	    	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	    glBindVertexArray(0);
	}
	
	// Destructeur
	GLShapeInstance::~GLShapeInstance(){
	    glDeleteBuffers(1, &vbo);
	    glDeleteVertexArrays(1, &vao);
	}
}
