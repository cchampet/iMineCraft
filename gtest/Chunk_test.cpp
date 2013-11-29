#include "iminecraft/land/Chunk.hpp"
#include <omp.h>
#include "gtest/gtest.h"


using namespace iminecraft;


TEST(Chunk, construction) {
	Chunk chunk;
	int x = chunk.getXPosition();
	int z = chunk.getZPosition();

	EXPECT_EQ(chunk.getXPosition(), x);
	EXPECT_EQ(chunk.getZPosition(), z);
	
}
