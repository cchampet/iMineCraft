#ifndef __IMINECRAFT_WORLD_H__
#define __IMINECRAFT_WORLD_H__

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imac2gl3/shader_tools.hpp"
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/Cube.hpp"
#include "imac2gl3/MatrixStack.hpp"
#include "imac2gl3/TextureTool.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>




#include <cstring>
#include <array>
#include <sstream>

#include "iminecraft/land/Chunk.hpp"
#include "iminecraft/shapes/MeshChunk.hpp"
#include "iminecraft/land/CubeData.hpp"
#include "imac2gl3/shapes/GLShapeInstance.hpp"

#include "iminecraft/cameras/FirstPersonCamera.hpp"
#include "iminecraft/LightingManager.hpp"

using namespace std;

#define MAX_RANGE 16 // Nombre de Chunk en largeur, Multiple de 2 !!!  si 16, ca nous donne 16*16 chunk affichés


namespace iminecraft {
	class World {
		private:
            vector<iminecraft::Chunk> chunkVector;
            vector<imac2gl3::GLShapeInstance*> meshChunkVector;

            vector<iminecraft::Chunk> chunkInCreationVector;

			LightingManager lightingManager;

            int seed;

            int night;
 
		public:
			World(int _seed, int xPositionHero, int zPositionHero);
			~World();

			void setNight(int value){ night = value;};
			int getNight(){ return night;};

			void sendPointLightsToCG(GLuint Program, glm::mat4 viewMatrix){
				lightingManager.sendPointLights(Program, viewMatrix);
			};
			void removePointLight(int xPosRegard, int yPosRegard, int zPosRegard);

			/**
			 * If a chunk is in creation, he does the next part of the generation
			 */
			void completeCreationOfChunk(int xPositionHero, int zPositionHero);

			void deleteMeshChunk(int xPositionChunk, int zPositionChunk);

			GLShapeInstance* getGLShapeInstance(int xPos, int zPos){
                for (size_t i = 0; i < meshChunkVector.size(); ++i)
					if(meshChunkVector.at(i)->getXPosition() == xPos)
						if(meshChunkVector.at(i)->getZPosition() == zPos)
							return meshChunkVector.at(i);

				return meshChunkVector.at(0);
            };

            void fillStorage(vector<iminecraft::CubeData> cubeData, int x, int z){
                meshChunkVector.push_back(new imac2gl3::GLShapeInstance(iminecraft::MeshChunk(cubeData)));
                meshChunkVector.back()->setXPosition(x);
                meshChunkVector.back()->setZPosition(z);
            };

            inline imac2gl3::GLShapeInstance* getMesh(size_t i){ return meshChunkVector.at(i); };

			/**
			 * Accessor to render the World
			 */
			vector<iminecraft::Chunk> getChunkVector(){ return chunkVector; };
			
			int getSizeChunkVector(){ return chunkVector.size(); };

			/**
			 * Use to manage the chunkVector
			 *
			 * if the main character is too far of a chunk, we pop it from the chunkVector
			 * if the main character is too close of a chunk who is not in the chunkVector, we push it with readFileForChunk()
			 */
			void manageChunkVector(int xPositionHero, int zPositionHero);

			void clearAllChunksAndRefreshToOrigin();

			void refreshMeshChunk(int xPositionChunk, int zPositionChunk, vector<iminecraft::CubeData> cubeDateVector);

			/**
			 * return the value of the right cube
			 */
			int getValue(glm::vec3 pos);

			/**
			 * return the position in the chunkVector of the chunk who has the block we need
			 */
			int getChuckFromPosition(float x, float z);

			void changeTypeOfABlock(int x, int y, int z, int type, int rightChunk);
			int changeDurabilityOfABlock(int x, int y, int z, int rightChunk);


	};
}

#endif
