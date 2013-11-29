#include "iminecraft/land/CubeData.hpp"
#include "gtest/gtest.h"

using namespace iminecraft;

TEST(CubeData, construction) {
	CubeData cube;
	int type = cube.getType();
	int dura = cube.getDurability();

	EXPECT_EQ(cube.getType(), type);
	EXPECT_EQ(cube.getDurability(), dura);

}

TEST(CubeData_setType, set_type) {
	CubeData cube;
	int type = 5;
	cube.setType(type);
	EXPECT_EQ(cube.getType(), type);
	EXPECT_EQ(cube.getDurability(), 1);
}

TEST(CubeData_setDurability, set_durability) {
	CubeData cube;
	int durability = 5;
	cube.setDurability(durability);
	EXPECT_EQ(cube.getDurability(), durability);
}
