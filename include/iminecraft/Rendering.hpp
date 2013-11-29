#ifndef __IMINECRAFT_RENDERING_H__
#define __IMINECRAFT_RENDERING_H__

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <cstdlib>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imac2gl3/shader_tools.hpp"
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/GLShapeInstance.hpp"
#include "imac2gl3/MatrixStack.hpp"
#include "imac2gl3/TextureTool.hpp"
#include "iminecraft/characters/CharactersGestion.hpp"
#include "iminecraft/land/Chunk.hpp"

#include "iminecraft/World.hpp"

#include "iminecraft/cameras/FirstPersonCamera.hpp"

#include "iminecraft/lighting.hpp"

using namespace std;

namespace iminecraft {
	class Rendering {
		private:
			int WINDOW_WIDTH, WINDOW_HEIGHT;

			// GLSL
            GLuint Program;

            // Uniform
            GLint projectionMatrixLocation;
			GLint modelViewMatrixLocation;
			GLint normalMatrixLocation;
			GLint lightActivatedLocation;

			GLint isSkyboxLocation;
			GLint nightActivatedLocation;

            glm::mat4 perspective;

            // MatrixStack for the Location of each thing we want to draw
            MatrixStack modelViewStack;
            
            // Vector used to stock each texture
			vector<TextureTool> textureVector;

			// reference to the world, used to stock Chunk and manage them
            iminecraft::World& world;
			// reference to the Camera
			iminecraft::FreeFlyCamera& camera;

			imac2gl3::GLShapeInstance cube;
			imac2gl3::GLShapeInstance skybox;

			imac2gl3::GLShapeInstance planeIntro;

			imac2gl3::GLShapeInstance cowShape;
			imac2gl3::GLShapeInstance sheepShape;
			imac2gl3::GLShapeInstance pigShape;
			imac2gl3::GLShapeInstance chickenShape;


			imac2gl3::GLShapeInstance monsterShape;
			//imac2gl3::GLShapeInstance skeletonShape;

			CharactersGestion& charactersGestion;

		public:
			Rendering(World& c_world, FreeFlyCamera& c_camera, CharactersGestion& c_charactersGestion);
			~Rendering();

			/**
			 * use to initialize each thing we need
			 * call InitUniformParams, InitTextures, etc..
			 */
			void Init();


			void setPerspective();


			/**
			 * init every uniformParams we need for GLSL
			 */
			void InitUniformParams();

			/**
			 * init each texture we will need
			 */
            void InitTextures();
			
			/**
			 * Loop Render
			 */
			void renderWithIntro(bool intro);

			/**
			 * get ChunkVector from the World and renderize each of them
			 */
			// void renderWorld(); // with blocks
			void renderWorldFromMeshVector(); // with mesh of chunk

			void renderCharacter();

			void renderNeutrals();

			void renderMonsters();

			void renderLogo();

			void renderHUD();

			void renderSkybox();
	};
}

#endif
