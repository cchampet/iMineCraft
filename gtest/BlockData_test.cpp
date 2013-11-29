#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "iminecraft/land/BlockData.hpp"

using namespace std;

using namespace iminecraft;

TEST(BlockData, construction){
	BlockData bd;
	string name0 = "DIRT";
	string name1 = "SAND";
	string name2 = "GRAVEL";
	string name3 = "STONE";
	string name4 = "COBBLESTONE";
	string texture0 = "images/003-terre.png";
	string texture1 = "images/012-sable.png";
	string texture2 = "images/013-gravier.png";
	string texture3 = "images/001-stone.png";
	string texture4 = "images/004-gravat.png";
	int durability0 = 25;
	int durability1 = 10;
	int durability2 = 35;
	int durability3 = 50;
	int durability4 = 60;

	EXPECT_EQ(name0, bd.getName(0));
	EXPECT_EQ(name1, bd.getName(1));
	EXPECT_EQ(name2, bd.getName(2));
	EXPECT_EQ(name3, bd.getName(3));
	EXPECT_EQ(name4, bd.getName(4));

	EXPECT_EQ(texture0, bd.getTextures(0));
	EXPECT_EQ(texture1, bd.getTextures(1));
	EXPECT_EQ(texture2, bd.getTextures(2));
	EXPECT_EQ(texture3, bd.getTextures(3));
	EXPECT_EQ(texture4, bd.getTextures(4));

	EXPECT_EQ(durability0, bd.getDurability(0));
	EXPECT_EQ(durability1, bd.getDurability(1));
	EXPECT_EQ(durability2, bd.getDurability(2));
	EXPECT_EQ(durability3, bd.getDurability(3));
	EXPECT_EQ(durability4, bd.getDurability(4));
}



