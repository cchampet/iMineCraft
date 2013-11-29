#include <glm/glm.hpp>
#include <cmath>
#include "iminecraft/cameras/FirstPersonCamera.hpp"
#include "gtest/gtest.h"

using namespace iminecraft;

TEST(FirstPersonCamera, construction){
	FirstPersonCamera FPC;
	EXPECT_EQ(glm::vec3(0.f, 0.f, 0.f), FPC.getPosition());
	EXPECT_EQ(glm::vec2(M_PI, 0.f), FPC.getAngles());
}

TEST(FirstPersonCamera, set_position){
	FirstPersonCamera FPC;
	FPC.setPosition(glm::vec3(1.f, .5f, 2.f));
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FPC.getPosition());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), FPC.getPosition());
}

TEST(FirstPersonCamera, set_angles){
	FirstPersonCamera FPC;
	float x = M_PI*.25;
	float y = -M_PI*.25;
	FPC.setAngles(x, y);
	EXPECT_NE(glm::vec2(M_PI, 0.f), FPC.getAngles());
	EXPECT_EQ(x, FPC.getAngles().x);
	EXPECT_EQ(y, FPC.getAngles().y);
}

TEST(FirstPersonCamera, set_camera){
	FirstPersonCamera FPC;
	FPC.setCamera(glm::vec3(1.f, .5f, 2.f), M_PI*.25, -M_PI*.25);
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FPC.getPosition());
	EXPECT_NE(glm::vec2(M_PI, 0.f), FPC.getAngles());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), FPC.getPosition());
	EXPECT_EQ(glm::vec2(M_PI*.25, -M_PI*.25), FPC.getAngles());
}

TEST(FirstPersonCamera, copy_construction){
	FirstPersonCamera FPC;
	FPC.setCamera(glm::vec3(1.f, .5f, 2.f), M_PI*.25, -M_PI*.25);
	FirstPersonCamera copy = FPC;
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), copy.getPosition());
	EXPECT_NE(glm::vec2(M_PI, 0.f), copy.getAngles());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), copy.getPosition());
	EXPECT_EQ(glm::vec2(M_PI*.25, -M_PI*.25), copy.getAngles());
}

TEST(FirstPersonCamera, move_front){
	FirstPersonCamera FPC;
	FPC.rotateUp(.25f);
	FPC.moveFront(.5f);
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FPC.getPosition());
	EXPECT_LT(FPC.getPosition().z, 0.f);
	FPC.rotateLeft(90.f);
	FPC.moveFront(.5f);
	EXPECT_LT(FPC.getPosition().x, 0.f);
	EXPECT_EQ(FPC.getPosition().y, 0.f);
}

TEST(FirstPersonCamera, move_left){
	FirstPersonCamera FPC;
	FPC.moveLeft(.5f);
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), FPC.getPosition());
	EXPECT_LT(FPC.getPosition().x, 0.f);
}

TEST(FirstPersonCamera, rotate_up){
	FirstPersonCamera FPC;
	FPC.rotateUp(.25f);
	EXPECT_LT(0.f, FPC.getAngles().y);
	FPC.rotateUp(2*M_PI);
	EXPECT_LT(FPC.getAngles().y, M_PI);
}

TEST(FirstPersonCamera, rotate_left){
	FirstPersonCamera FPC;
	FPC.rotateLeft(.25f);
	EXPECT_EQ(0, FPC.getAngles().y);
	EXPECT_LT(M_PI, FPC.getAngles().x);
	FPC.rotateLeft(-.5f);
	EXPECT_GT(M_PI, FPC.getAngles().x);
}
