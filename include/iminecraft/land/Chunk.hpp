/*
 * chunk.hpp
 *
 *  Created on: 7 déc. 2012
 *      Author: jérémy
 */
#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <cstring>
#include <sstream>

#include "imac2gl3/shapes/Cube.hpp"
#include "iminecraft/land/CubeData.hpp"
#include "iminecraft/shapes/MeshChunk.hpp"
#include "imac2gl3/shapes/GLShapeInstance.hpp"

#include "iminecraft/lighting.hpp"

// Libnoise
#include <noise/noise.h>
#include "noise/noiseutils.h"

using namespace noise;


#define M_WIDTH 	16
#define M_HEIGHT 	128
#define M_DEEP 		16

using namespace std;

namespace iminecraft {

	/* 16 * 16 * 8 cubes in a chunck */
	class Chunk {
		private:
			int xPosition;
			int zPosition;

			int seed; // used to generated the land

			int stepCreation;

			vector<iminecraft::CubeData> cubeDataVector;
		protected:
		public:
			Chunk(){stepCreation = 0;};
			Chunk(int _seed, int xPos, int zPos);   // ctor calling file			
			~Chunk();

			int getStepCreation(){ return stepCreation;};

			const vector<iminecraft::CubeData> getCubeDataVector(){ return cubeDataVector; };
	
        	//string getPositionName(){ return positionName;};
        	int getXPosition(){ return xPosition;};
        	int getZPosition(){ return zPosition;};

        	vector<PointLight> getPointLights();


        	/**
			 * generate a new Chunk
			 */
        	void stepByStepCreation();

        	void addLava();
			void addWater();
			void addSand();
			void addStone();
			void addDirt();
			void addTree();



        	/**
        	 * Check if the vector has the right, if not, complete him with '0'
        	 */
        	void checkSizeChunk();

	        // bool checkFaceVisibility_top(int x, int y, int z){ return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_top; };
	        // bool checkFaceVisibility_bottom(int x, int y, int z){ return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_bottom; };
	        // bool checkFaceVisibility_left(int x, int y, int z){ return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_left; };
	        // bool checkFaceVisibility_right(int x, int y, int z){ return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_right; };
	        // bool checkFaceVisibility_back(int x, int y, int z){ return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_back; };
	        // bool checkFaceVisibility_front(int x, int y, int z){ return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_front; };

        	/**
        	 * Test each block to see if he has to be render or not (no need to render a block who can't be seen)
        	 */
        	// void checkVisibleBlocks();

        	/**
        	 * Test each face of each block to see if visible or not
        	 */
        	// void checkEachFace(int x, int y, int z);
										
			// Access element Chunk(), i.e a vector of integers.
			int getVal(unsigned int x, unsigned int y, unsigned int z);
			int getDurability(unsigned int x, unsigned int y, unsigned int z);

			void changeBlock(int x, int y, int z, int type){
				cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).setType(type);
			}

			int changeDurability(int x, int y, int z){
				cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).setDurability(cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).getDurability()-1);
				return cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).getDurability();
			}

			// Access to the variable Visible of the block
			// bool getVisible(unsigned int x, unsigned int y, unsigned int z);

			/**
			 * Create a heightMap with Perlin Noise and fill the chunk with this one
			 */
			void addSomeBlocksFromNoise(int seed, int type, int yMin, int yMax, int epaisseur);

			/**
			 * Read Chunk in file
			 *
			 * return true if succeed
			 * if false returned, it's time to generate a new chunk
			 */
			bool readChunkFromFile();

			/**
			 * Save Chunk in file
			 */
			void saveChunkInFile();
	};
}

#endif //__CHUNK_H__
