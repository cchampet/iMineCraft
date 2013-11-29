#ifndef __BLOCKDATA_H__
#define __BLOCKDATA_H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

namespace iminecraft {
	class BlockData {
		private:
			vector<string> name;
			vector<string> textures;
			vector<int> durability;

		public:
			BlockData();
			~BlockData();

			string getName(int id);
			string getTextures(int id);
			int getDurability(int id);

			void displayAllData(); // to test each vector
	};
}

#endif
