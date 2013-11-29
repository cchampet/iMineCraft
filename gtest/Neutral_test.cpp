#include <glm/glm.hpp>
#include <cmath>
#include "iminecraft/characters/Neutral.hpp"
#include "gtest/gtest.h"
#include "limits.h"

using namespace iminecraft;

TEST(Neutral, construction_cow){
	// cow
	Neutral n1 = Neutral(cow);
	EXPECT_EQ(cow, n1.type());
	EXPECT_EQ(float(M_PI), n1.direction());
	EXPECT_EQ(5., n1.maxLife());
	EXPECT_EQ(n1.maxLife(), n1.life());
	EXPECT_EQ(.01f, n1.speed());
}

TEST(Neutral, construction_sheep){
	// sheep
	Neutral n2 = Neutral(sheep);
	EXPECT_EQ(sheep, n2.type());
	EXPECT_EQ(float(M_PI), n2.direction());
	EXPECT_EQ(3., n2.maxLife());
	EXPECT_EQ(n2.maxLife(), n2.life());
	EXPECT_EQ(.05f, n2.speed());
}

TEST(Neutral, construction_pig){
	// pig
	Neutral n3 = Neutral(pig);
	EXPECT_EQ(pig, n3.type());
	EXPECT_EQ(float(M_PI), n3.direction());
	EXPECT_EQ(7., n3.maxLife());
	EXPECT_EQ(n3.maxLife(), n3.life());
	EXPECT_EQ(.01f, n3.speed());
}

TEST(Neutral, construction_chicken){
	// chicken
	Neutral n4 = Neutral(chicken);
	EXPECT_EQ(chicken, n4.type());
	EXPECT_EQ(float(M_PI), n4.direction());
	EXPECT_EQ(1., n4.maxLife());
	EXPECT_EQ(n4.maxLife(), n4.life());
	EXPECT_EQ(.02f, n4.speed());
}
