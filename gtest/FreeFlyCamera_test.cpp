#include <glm/glm.hpp>
#include <cmath>
#include "iminecraft/cameras/FreeFlyCamera.hpp"
#include "gtest/gtest.h"

using namespace iminecraft;

TEST(FreeFlyCamera, construction){
	FreeFlyCamera FFC;
	EXPECT_EQ(glm::vec3(0.f, 0.f, 0.f), FFC.getPosition());
	EXPECT_EQ(glm::vec2(M_PI, 0.f), FFC.getAngles());
}

TEST(FreeFlyCamera, set_position){
	FreeFlyCamera FFC;
	FFC.setPosition(glm::vec3(1.f, .5f, 2.f));
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FFC.getPosition());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), FFC.getPosition());
}

TEST(FreeFlyCamera, set_angles){
	FreeFlyCamera FFC;
	float x = M_PI*.25;
	float y = -M_PI*.25;
	FFC.setAngles(x, y);
	EXPECT_NE(glm::vec2(M_PI, 0.f), FFC.getAngles());
	EXPECT_EQ(x, FFC.getAngles().x);
	EXPECT_EQ(y, FFC.getAngles().y);
	EXPECT_EQ(glm::vec3(0.f, 0.f, 0.f), FFC.getPosition());
}

TEST(FreeFlyCamera, set_camera){
	FreeFlyCamera FFC;
	FFC.setCamera(glm::vec3(1.f, .5f, 2.f), M_PI*.25, -M_PI*.25);
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FFC.getPosition());
	EXPECT_NE(glm::vec2(M_PI, 0.f), FFC.getAngles());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), FFC.getPosition());
	EXPECT_EQ(glm::vec2(M_PI*.25, -M_PI*.25), FFC.getAngles());
}

TEST(FreeFlyCamera, copy_construction){
	FreeFlyCamera FFC;
	FFC.setCamera(glm::vec3(1.f, .5f, 2.f), M_PI*.25, -M_PI*.25);
	FreeFlyCamera copy = FFC;
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), copy.getPosition());
	EXPECT_NE(glm::vec2(M_PI, 0.f), copy.getAngles());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), copy.getPosition());
	EXPECT_EQ(glm::vec2(M_PI*.25, -M_PI*.25), copy.getAngles());
}

TEST(FreeFlyCamera, move_front){
	FreeFlyCamera FFC;
	FFC.moveFront(.5f);
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FFC.getPosition());
	EXPECT_LT(FFC.getPosition().z, 0.f);
}

TEST(FreeFlyCamera, move_left){
	FreeFlyCamera FFC;
	FFC.moveLeft(.5f);
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FFC.getPosition());
	EXPECT_LT(FFC.getPosition().x, 0.f);
}

TEST(FreeFlyCamera, rotate_up){
	FreeFlyCamera FFC;
	FFC.rotateUp(.25f);
	EXPECT_LT(0.f, FFC.getAngles().y);
}

TEST(FreeFlyCamera, rotate_left){
	FreeFlyCamera FFC;
	FFC.rotateLeft(.25f);
	EXPECT_LT(M_PI, FFC.getAngles().x);
}
