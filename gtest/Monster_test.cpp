#include <glm/glm.hpp>
#include "gtest/gtest.h"
#include "iminecraft/characters/Monster.hpp"

using namespace iminecraft;

TEST(Monster, construction){
	Monster m;
	EXPECT_EQ(glm::vec3(5.,87.,0.), m.position());
	EXPECT_EQ(float(M_PI), m.direction());
	EXPECT_EQ(3., m.maxLife());
	EXPECT_EQ(m.maxLife(), m.life());
	EXPECT_EQ(.1f, m.speed());
	EXPECT_EQ(8., m.vision());
}

TEST(Monster, new_vision){
	Monster m;
	m.vision(20.);
	EXPECT_EQ(20., m.vision());
}
