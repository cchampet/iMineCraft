#include "iminecraft/World.hpp"
#include <cmath>

namespace iminecraft {
	// constructor
	World::World(int _seed, int xPositionHero, int zPositionHero): lightingManager(16, 75){
		seed = _seed;
		night = 0;

		// float chunkPercent = 100.f/(float)(MAX_RANGE*MAX_RANGE);
		// float countPercent = 0;
		// Uint32 timeStart = SDL_GetTicks();
		// for(int x = 0; x < MAX_RANGE; ++x){
		// 	for (int z = 0; z < MAX_RANGE; ++z){				
		// 		int xPos = x - (MAX_RANGE/2);
		// 		int zPos = z - (MAX_RANGE/2);
				
		// 		chunkVector.push_back(iminecraft::Chunk(seed, xPos, zPos));
		// 	}
		// 	countPercent += MAX_RANGE*chunkPercent; // mise a jour de l'affichage tous les 16 chunks
		// 	cout << "generation des chunks : " << floor(countPercent) << " %" << endl;
		// }
		// Uint32 timeEnd = SDL_GetTicks();
		// cout << "generation terminée, cela a pris : " << (timeEnd - timeStart) << " ms pour créer " << MAX_RANGE*MAX_RANGE << " chunks" << endl;


		// countPercent = 0;
		// timeStart = SDL_GetTicks();
		// for (size_t i = 0; i < chunkVector.size(); ++i){
		// 	fillStorage(chunkVector.at(i).getCubeDataVector(), chunkVector.at(i).getXPosition(), chunkVector.at(i).getZPosition());
		// 	if(i%MAX_RANGE == 0){
		// 		countPercent += MAX_RANGE*chunkPercent; // mise a jour de l'affichage tous les 16 chunks
		// 		cout << "generation des chunks : " << floor(countPercent) << " %" << endl;
		// 	}
		// }
		// timeEnd = SDL_GetTicks();
		// cout << "generation des mesh terminée, cela a pris : " << (timeEnd - timeStart) << " ms " << endl;

		int xChunk = floor(xPositionHero/16.f);
		int zChunk = floor(zPositionHero/16.f);
		for(int x = 0; x < MAX_RANGE; ++x){
			for (int z = 0; z < MAX_RANGE; ++z){				
				int xPos = x - (MAX_RANGE/2) + xChunk;
				int zPos = z - (MAX_RANGE/2) + zChunk;

				chunkInCreationVector.push_back(iminecraft::Chunk(seed, xPos, zPos));
			}
		}
	}

	void World::removePointLight(int xPosRegard, int yPosRegard, int zPosRegard){
		lightingManager.removePointLight(xPosRegard, yPosRegard, zPosRegard);
	}

	void World::completeCreationOfChunk(int xPositionHero, int zPositionHero){
		if(!chunkInCreationVector.empty()){
			// get closest Chunk of the Hero
			size_t index = 0;
			float distance = 1000000.f;
			for(size_t i = 0; i < chunkInCreationVector.size(); ++i){
				float distanceChunkHero = abs((chunkInCreationVector.at(i).getXPosition()*16)-xPositionHero) + abs((chunkInCreationVector.at(i).getZPosition()*16)-zPositionHero);
				if(distanceChunkHero < distance){
					index = i;
					distance = distanceChunkHero;
				}
			}

			if(chunkInCreationVector.at(index).getStepCreation() >= 8){
				// generation ended
				chunkVector.push_back(chunkInCreationVector.at(index));
				chunkInCreationVector.erase(chunkInCreationVector.begin()+index);

				fillStorage(chunkVector.back().getCubeDataVector(), chunkVector.back().getXPosition(), chunkVector.back().getZPosition());
				vector<PointLight> pointLightVector = chunkVector.back().getPointLights();
				for(unsigned int i = 0; i < pointLightVector.size(); ++i){
					lightingManager.addPointLight(pointLightVector.at(i));
				}
			}else{
				chunkInCreationVector.at(index).stepByStepCreation();
			}
		}
	}


	int World::changeDurabilityOfABlock(int x, int y, int z, int rightChunk){
		int durability = chunkVector.at(rightChunk).changeDurability(x, y, z);
		if(durability == 0)
			changeTypeOfABlock(x, y, z, 0, rightChunk);
		return durability;
	}

	void World::changeTypeOfABlock(int x, int y, int z, int type, int rightChunk){
		if(type == 8){
			// glowstone
			int xPos = chunkVector.at(rightChunk).getXPosition();
			int zPos = chunkVector.at(rightChunk).getZPosition();
			PointLight pointLight;
	    	pointLight.position = glm::vec3((xPos*16)+x+0.5f,y+0.5f,(zPos*16)+z+0.5f);
	    	pointLight.intensity = glm::vec3(10,5,5);
			lightingManager.addPointLight(pointLight);
		}
		
		chunkVector.at(rightChunk).changeBlock(x, y, z, type);
		//chunkVector.at(rightChunk).checkVisibleBlocks();
		chunkVector.at(rightChunk).saveChunkInFile();
	}
	
	void World::manageChunkVector(int xPositionHero, int zPositionHero){
		int xPos = floor(xPositionHero/16);
		int zPos = floor(zPositionHero/16);
		for(size_t i = 0; i < chunkVector.size(); ++i){
			// RIGHT
			int xPositionChunk = chunkVector.at(i).getXPosition();
			int zPositionChunk = chunkVector.at(i).getZPosition();
			if(xPositionChunk > xPos + (MAX_RANGE*0.5) -1){
				chunkVector.erase(chunkVector.begin() + i); // chunk too far on the right
				chunkInCreationVector.push_back(iminecraft::Chunk(seed, xPositionChunk - MAX_RANGE, zPositionChunk));
				deleteMeshChunk(xPositionChunk, zPositionChunk);
				break;			
			}
			// LEFT
			if(xPositionChunk < xPos - (MAX_RANGE*0.5)){
				chunkVector.erase(chunkVector.begin() + i); // chunk too far on the right
				chunkInCreationVector.push_back(iminecraft::Chunk(seed, xPositionChunk + MAX_RANGE, zPositionChunk));
				deleteMeshChunk(xPositionChunk, zPositionChunk);
				break;
			}

			// FRONT
			if(zPositionChunk < zPos - (MAX_RANGE*0.5)){
				chunkVector.erase(chunkVector.begin() + i); // chunk too far on the right
				chunkInCreationVector.push_back(iminecraft::Chunk(seed, xPositionChunk, zPositionChunk + MAX_RANGE));
				deleteMeshChunk(xPositionChunk, zPositionChunk);
				break;
			}
			// BACK
			if(zPositionChunk > zPos + (MAX_RANGE*0.5) -1){
				chunkVector.erase(chunkVector.begin() + i); // chunk too far on the right
				chunkInCreationVector.push_back(iminecraft::Chunk(seed, xPositionChunk, zPositionChunk - MAX_RANGE));
				deleteMeshChunk(xPositionChunk, zPositionChunk);
				break;
			}
		}
	}

	void World::clearAllChunksAndRefreshToOrigin(){
		chunkVector.clear();
		chunkInCreationVector.clear();

		vector<imac2gl3::GLShapeInstance*>::iterator it;
		for(it = meshChunkVector.begin(); it != meshChunkVector.end();){
			delete * it;
			it = meshChunkVector.erase(it);
		}
		meshChunkVector.clear();

		for(int x = 0; x < MAX_RANGE; ++x){
			for (int z = 0; z < MAX_RANGE; ++z){
				int xPos = x - (MAX_RANGE/2);
				int zPos = z - (MAX_RANGE/2);

				chunkInCreationVector.push_back(iminecraft::Chunk(seed, xPos, zPos));
			}
		}
	}

	void World::deleteMeshChunk(int xPositionChunk, int zPositionChunk){
		for (size_t j = 0; j < meshChunkVector.size(); ++j){
			int xPositionMeshChunk = meshChunkVector.at(j)->getXPosition();
			int zPositionMeshChunk = meshChunkVector.at(j)->getZPosition();
			if(xPositionMeshChunk == xPositionChunk){
				if(zPositionMeshChunk == zPositionChunk){
					imac2gl3::GLShapeInstance* shapePointer = meshChunkVector.at(j);
					meshChunkVector.erase(meshChunkVector.begin() + j);
					delete shapePointer;
	                break;
				}
			}
		}
	}

	void World::refreshMeshChunk(int xPositionChunk, int zPositionChunk, vector<iminecraft::CubeData> cubeDataVector){
		for (size_t j = 0; j < meshChunkVector.size(); ++j){
			int xPositionMeshChunk = meshChunkVector.at(j)->getXPosition();
			int zPositionMeshChunk = meshChunkVector.at(j)->getZPosition();
			if(xPositionMeshChunk == xPositionChunk){
				if(zPositionMeshChunk == zPositionChunk){
					imac2gl3::GLShapeInstance* shapePointer = meshChunkVector.at(j);
					meshChunkVector.erase(meshChunkVector.begin() + j);
					delete shapePointer;
					
					meshChunkVector.push_back(new imac2gl3::GLShapeInstance(iminecraft::MeshChunk(cubeDataVector)));
	                meshChunkVector.back()->setXPosition(xPositionMeshChunk); // il est toujours à la meme place
	                meshChunkVector.back()->setZPosition(zPositionMeshChunk);

	                break;
				}
			}
		}
	}

	int World::getValue(glm::vec3 pos){
		int rightChunk = getChuckFromPosition(pos.x, pos.z);
		if(rightChunk < 0){
			// whoops, nothing has been found
			return 0;
		}
		return chunkVector.at(rightChunk).getVal((size_t)pos.x%16,(size_t)pos.y,(size_t)pos.z%16);
	}

	int World::getChuckFromPosition(float x, float z){
		int posX = floor(x*0.0625); // floor(x/16)
		int posZ = floor(z*0.0625); // floor(z/16)
		for(size_t i = 0; i < chunkVector.size(); ++i){
			if(posX == chunkVector.at(i).getXPosition()
				&& posZ == chunkVector.at(i).getZPosition()){
				return i;
			}
		}
		return -1;
	}

	// destructor
	World::~World(){
		chunkVector.clear();

		vector<imac2gl3::GLShapeInstance*>::iterator it;
		for(it = meshChunkVector.begin(); it != meshChunkVector.end();){
			delete * it;
			it = meshChunkVector.erase(it);
		}
		meshChunkVector.clear();
	}
}
