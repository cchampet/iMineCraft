/*
 * chunk.hpp
 *
 *  Created on: 7 déc. 2012
 *      Author: jérémy
 */
 
#include "iminecraft/land/Chunk.hpp"
#include <omp.h>

namespace iminecraft {
	// constructor
	Chunk::Chunk(int _seed, int xPos, int zPos){
		xPosition = xPos;
		zPosition = zPos;
		seed = _seed;
		stepCreation = 0;
	}

	void Chunk::stepByStepCreation(){
		switch(stepCreation){
			case 1:
				addLava();
				break;
			case 2:
				addWater();
				break;
			case 3:
				addSand();
				break;
			case 4:
				addStone();
				break;
			case 5:
				addDirt();
				break;
			case 6:
				addTree();
				break;
			case 7:
				// to avoid errors
		  		checkSizeChunk();
				// checkVisibleBlocks();
				saveChunkInFile();
				break;
			default:
				// start
				if(!readChunkFromFile()){
					// fail to open file, it's time to generate a new one
					checkSizeChunk(); // fill Chunk with zero
				}else{
					stepCreation = 6; // almost end of the generation
				}				
				break;
		}
		stepCreation++;
	}

	vector<PointLight> Chunk::getPointLights(){
		vector<PointLight> storePointLight;
		for (int x = 0; x < M_WIDTH; ++x)
			for (int y = 0; y < M_HEIGHT; ++y)
				for (int z = 0; z < M_DEEP; ++z)
					if(getVal(x,y,z) == 8){
						// GlowStone
						PointLight PL;
						PL.position =  glm::vec3((xPosition*16)+x+0.5f,y+0.5f,(zPosition*16)+z+0.5f);
	    				PL.intensity = glm::vec3(10,5,5);
						storePointLight.push_back(PL);
					}

		return storePointLight;				
	}

	// acces to element cube i of chunk by writting this : Chunk(i); or is it Chunk.cubes(i); ?
	// not working yet
	int Chunk::getVal(unsigned int x, unsigned int y, unsigned int z) {
		if(x>=0 && x < M_WIDTH && y>=0 && y<M_HEIGHT && z>=0 && z<M_DEEP)
			return cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType();
		else if(y<=0)
				return 1; // bottom limit of the chunk
		else
			return -1; //wrong chunk
	}

	int Chunk::getDurability(unsigned int x, unsigned int y, unsigned int z) {
		if(x>=0 && x < M_WIDTH && y>=0 && y<M_HEIGHT && z>=0 && z<M_DEEP)
			return cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getDurability();
		else
			return -1; //wrong chunk
	}

	// bool Chunk::getVisible(unsigned int x, unsigned int y, unsigned int z) {
	// 	if(x>=0 && x < M_WIDTH && y>=0 && y<M_HEIGHT && z>=0 && z<M_DEEP)
	// 		return cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getVisible();
	// 	else
	// 		return false; //wrong chunk
	// }

	void Chunk::addLava(){
		// LAVA
		for (int x = 0; x < M_WIDTH; ++x)
			for (int z = 0; z < M_DEEP; ++z)
				for (int y = 0; y < 15; ++y)
					cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(5);
	}

	void Chunk::addWater(){
		// WATER
		for (int x = 0; x < M_WIDTH; ++x)
			for (int z = 0; z < M_DEEP; ++z)
				for (int y = 24; y < 48; ++y)
					cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(1);
	}

	void Chunk::addSand(){
		// SAND
		addSomeBlocksFromNoise(seed+18948, 2, 32, 127, 3);
		addSomeBlocksFromNoise(seed+56468, 2, 32, 127, 3);
	}

	void Chunk::addStone(){
		// STONE
		addSomeBlocksFromNoise(seed+86454, 3, 15, 127, 10);
		addSomeBlocksFromNoise(seed+268944, 3, 15, 127, 10);
	}

	void Chunk::addDirt(){
		// DIRT
		addSomeBlocksFromNoise(seed+787454, 4, 32, 127, 5);
		addSomeBlocksFromNoise(seed+365464, 4, 32, 127, 5);
	}

	void Chunk::addTree(){
		// TREE
		for (int x = 2; x < M_WIDTH-2; ++x){
			for (int z = 2; z < M_DEEP-2; ++z){
				for (int y = 40; y < 100; ++y){
					if(cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 4 
						&& cubeDataVector.at(x + ((y+1)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 0

						&& cubeDataVector.at(x+1 + ((y+1)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x-1 + ((y+1)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x + ((y+1)*M_WIDTH) + ((z+1)*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x + ((y+1)*M_WIDTH) + ((z-1)*M_WIDTH*M_HEIGHT)).getType() == 0

						&& cubeDataVector.at(x+2 + ((y+1)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x-2 + ((y+1)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x + ((y+1)*M_WIDTH) + ((z+2)*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x + ((y+1)*M_WIDTH) + ((z-2)*M_WIDTH*M_HEIGHT)).getType() == 0

						&& cubeDataVector.at(x+1 + ((y+1)*M_WIDTH) + ((z+1)*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x-1 + ((y+1)*M_WIDTH) + ((z+1)*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x+1 + ((y+1)*M_WIDTH) + ((z-1)*M_WIDTH*M_HEIGHT)).getType() == 0
						&& cubeDataVector.at(x-1 + ((y+1)*M_WIDTH) + ((z-1)*M_WIDTH*M_HEIGHT)).getType() == 0

						&& cubeDataVector.at(x+1 + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 4
						&& cubeDataVector.at(x-1 + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).getType() == 4
						&& cubeDataVector.at(x + (y*M_WIDTH) + ((z+1)*M_WIDTH*M_HEIGHT)).getType() == 4
						&& cubeDataVector.at(x + (y*M_WIDTH) + ((z-1)*M_WIDTH*M_HEIGHT)).getType() == 4){

						// create tree
						for (int i = 1; i < 8; ++i){
							cubeDataVector.at(x + ((y+i)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(6);

							if(i%2 == 0){
								cubeDataVector.at(x+1 + ((y+i)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(7);
								cubeDataVector.at(x-1 + ((y+i)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(7);
								cubeDataVector.at(x + ((y+i)*M_WIDTH) + ((z+1)*M_WIDTH*M_HEIGHT)).setType(7);
								cubeDataVector.at(x + ((y+i)*M_WIDTH) + ((z-1)*M_WIDTH*M_HEIGHT)).setType(7);
							}
						}
						cubeDataVector.at(x + ((y+8)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(7);
					}
				}
			}
		}
	}

	void Chunk::addSomeBlocksFromNoise(int seed, int type, int yMin, int yMax, int epaisseur){
		// Create the heightMap with Perlin Noise
		module::Perlin myModule;
		utils::NoiseMap heightMap;
		utils::NoiseMapBuilderPlane heightMapBuilder;
		myModule.SetPersistence(0.5);
        myModule.SetOctaveCount(4);
        myModule.SetFrequency (0.05);
		heightMapBuilder.SetSourceModule (myModule);
		heightMapBuilder.SetDestNoiseMap (heightMap);
		heightMapBuilder.SetDestSize (256, 256);
		heightMapBuilder.SetBounds(xPosition, xPosition+16, zPosition, zPosition+16);

		myModule.SetSeed(seed);
		heightMapBuilder.Build();
		for (int x = 0; x < M_WIDTH; ++x){
			for (int z = 0; z < M_DEEP; ++z){
				double returnedNoise = heightMap.GetValue(x, z);
				float absNoise = abs(returnedNoise);
				int height = (int)(absNoise * 48);
				height += 40;

				if(height > yMax) height = yMax;
				if(height < (yMin+epaisseur)) height = yMin+epaisseur;
				
				for (int y = 0; y < epaisseur; ++y)
					cubeDataVector.at(x + ((height-y)*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setType(type);
			}
		}
	}

	// void Chunk::checkEachFace(int x, int y, int z){
	//     // top
	//     if(getVal(x,y+1,z) > 0 && getVal(x,y+1,z) != 4) // il y a un cube
	//         cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_top = false;
	//     // bottom
	//     if(getVal(x,y-1,z) > 0 && getVal(x,y-1,z) != 4) // il y a un cube
	//         cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_bottom = false;
	//     // left
	//     if(getVal(x-1,y,z) > 0 && getVal(x-1,y,z) != 4) // il y a un cube
	//         cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_left = false;
	//     // right
	//     if(getVal(x+1,y,z) > 0 && getVal(x+1,y,z) != 4) // il y a un cube
	//         cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_right = false;
	//     // front
	//     if(getVal(x,y,z-1) > 0 && getVal(x,y,z-1) != 4) // il y a un cube
	//         cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_front = false;
	//     // back
	//     if(getVal(x,y,z+1) > 0 && getVal(x,y,z+1) != 4) // il y a un cube
	//         cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_back = false;


	//     // cas particulier : eau
	//     if(getVal(x,y,z) == 4){
	//     	// top
	// 	    if(getVal(x,y+1,z) == 4) // il y a un cube d'eau
	// 	        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_top = false;
	// 	    // bottom
	// 	    if(getVal(x,y-1,z) == 4) // il y a un cube d'eau
	// 	        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_bottom = false;
	// 	    // left
	// 	    if(getVal(x-1,y,z) == 4) // il y a un cube d'eau
	// 	        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_left = false;
	// 	    // right
	// 	    if(getVal(x+1,y,z) == 4) // il y a un cube d'eau
	// 	        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_right = false;
	// 	    // front
	// 	    if(getVal(x,y,z-1) == 4) // il y a un cube d'eau
	// 	        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_front = false;
	// 	    // back
	// 	    if(getVal(x,y,z+1) == 4) // il y a un cube d'eau
	// 	        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_back = false;
	//     }
	// }

	void Chunk::checkSizeChunk(){
		if(cubeDataVector.size() < M_WIDTH*M_HEIGHT*M_DEEP){
			// vector uncompleted
			for (int i = cubeDataVector.size(); i < M_WIDTH*M_HEIGHT*M_DEEP; ++i){
				cubeDataVector.push_back(iminecraft::CubeData(0));
			}
		}
	}

	// void Chunk::checkVisibleBlocks(){
	// 	// reset
	// 	for (int i = 0; i < M_WIDTH*M_HEIGHT*M_DEEP; ++i){
	// 		cubeDataVector.at(i).setVisible(true);
	// 		cubeDataVector.at(i).faceVisible_top = true;
	// 		cubeDataVector.at(i).faceVisible_bottom = true;
	// 		cubeDataVector.at(i).faceVisible_left = true;
	// 		cubeDataVector.at(i).faceVisible_right = true;
	// 		cubeDataVector.at(i).faceVisible_front = true;
	// 		cubeDataVector.at(i).faceVisible_back = true;
	// 	}
	// 	for (int x = 0; x < M_WIDTH; ++x){
	//         for (int y = 0; y < M_HEIGHT; ++y){
	//             for (int z = 0; z < M_DEEP; ++z){
	//             	if(getVal(x,y,z) == 0){
	//             		// de l'air : invisible
	//             		cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setVisible(false);
	//             	}else{
	//             		if(getVal(x, y, z) == 4){
	//             			// de l'eau
	//             			if(getVal(x+1, y, z) > 0 && getVal(x-1, y, z) > 0
	// 							                		&& getVal(x, y, z+1) > 0
	// 							                		&& getVal(x, y, z-1) > 0
	// 							                		&& getVal(x, y+1, z) > 0
	// 							                		&& getVal(x, y-1, z) > 0){
	//             				cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setVisible(false);
	// 							// tout autour n'est pas de l'air : on est pas invisible (faux si c'est de l'eau mais bon)
	//             			}
	//             		}else{
	//             			// autre chose
	//             			if(getVal(x+1, y, z) > 0 && getVal(x-1, y, z) > 0
	// 							                	&& getVal(x, y, z+1) > 0
	// 							                	&& getVal(x, y, z-1) > 0
	// 							                	&& getVal(x, y+1, z) > 0
	// 							                	&& getVal(x, y-1, z) > 0

	// 							                	&& getVal(x+1, y, z) != 4 	
	// 		                						&& getVal(x-1, y, z) != 4
	// 								                && getVal(x, y, z+1) != 4
	// 								                && getVal(x, y, z-1) != 4
	// 								                && getVal(x, y+1, z) != 4
	// 								                && getVal(x, y-1, z) != 4){
	// 		                	// Si tous les blocks autour ne sont pas du vide et ne sont pas de l'eau, on ne peut pas voir ce block !
	// 		                	cubeDataVector.at(x + (y*M_WIDTH) + (z*M_WIDTH*M_HEIGHT)).setVisible(false);
	// 	            		}
	// 	                }
	//             	}	                
	//             }
	//         }
	//     }

	//     for (int x = 0; x < 16; ++x){
	//   		for (int y = 0; y < 128; ++y){
	//   			for (int z = 0; z < 16; ++z){
	//   				if(getVisible(x,y,z)){
	//   					checkEachFace(x,y,z);
	//   				}else{
	// 			        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_top = false;
	// 			        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_bottom = false;
	// 			        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_left = false;
	// 			        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_right = false;
	// 			        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_front = false;
	// 			        cubeDataVector.at(x + (y * M_WIDTH) + (z * M_HEIGHT * M_WIDTH)).faceVisible_back = false;
	//   				}
	//   			}
	//   		}
	//   	}
	// }

	bool Chunk::readChunkFromFile(){
		ostringstream oss_X;
		oss_X << xPosition;
		ostringstream oss_Z;
		oss_Z << zPosition;
		string filePath = string("files/") + oss_X.str() + string("_") + oss_Z.str() + string(".chunk");

		ifstream chunkFile(filePath);
		//if(!chunkFile) throw ifstream::failure("fail to open file");
		if(!chunkFile) return false; // file do not exist

		int var;
	  	while(chunkFile >> var)
	  		cubeDataVector.push_back(var);

		chunkFile.close();
		return true;
	}

	void Chunk::saveChunkInFile(){
		ostringstream oss_X;
		oss_X << xPosition;
		ostringstream oss_Z;
		oss_Z << zPosition;
		string filePath = string("files/") + oss_X.str() + string("_") + oss_Z.str() + string(".chunk");

		ofstream chunkFile(filePath);
		if(!chunkFile.good()) throw ofstream::failure("'Save Chunk: fail to create file'");

		for (size_t i = 0; i < cubeDataVector.size(); ++i){
			chunkFile << cubeDataVector.at(i).getType();
			if((i+1)%M_WIDTH == 0)
				chunkFile << endl;
			else
				chunkFile << " ";
		}

		chunkFile.close();
	}

	// destructor
	Chunk::~Chunk(){
		cubeDataVector.clear();
	}
}
