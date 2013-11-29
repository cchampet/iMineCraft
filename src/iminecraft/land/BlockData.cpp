#include "iminecraft/land/BlockData.hpp"


namespace iminecraft {
	// Constructor
	BlockData::BlockData(){
		ifstream file_blockData("blockData");

		if(file_blockData){
	  		string word;
			while(file_blockData >> word){
				// name
				name.push_back(word);
				// textures
				if(file_blockData >> word)
					textures.push_back(word);
				// durability
				if(file_blockData >> word)
					durability.push_back(atoi(word.c_str()));
			}

			file_blockData.close();
		}
	}

	string BlockData::getName(int id){
		if(id > -1 && id < (int)name.size())
			return name.at(id);
		return "NULL";
	}

	string BlockData::getTextures(int id){
		if(id > -1 && id < (int)textures.size())
			return textures.at(id);
		return "TEXTURE_NULL.png";
	}

	int BlockData::getDurability(int id){
		if(id > -1 && id < (int)durability.size())
			return durability.at(id);
		return 1;
	}

	void BlockData::displayAllData(){
		for (int i = 0; i < (int)name.size(); ++i)
			cout << name[i] << ", texture :" << textures[i] << ", durability :" << durability[i] << endl;
	}

	// Destructor
	BlockData::~BlockData(){
		name.clear();
		textures.clear();
		durability.clear();
	}
}
