#include <glm/glm.hpp>
#include <cmath>
#include "iminecraft/characters/Character.hpp"
#include "gtest/gtest.h"
#include "limits.h"

using namespace iminecraft;

TEST(Character, construction){
	Character ch;
	EXPECT_EQ(glm::vec3(3.f, 128.f, 3.f), ch.position());
	EXPECT_EQ(float(M_PI), ch.direction());
	EXPECT_EQ(10., ch.maxLife());
	EXPECT_EQ(ch.maxLife(), ch.life());
	EXPECT_EQ(.1f, ch.speed());

	Character ch2 = Character(glm::vec3(1.f, 100.f, 2.f), M_PI*0.25, 5.5f, 1.5f);
	EXPECT_EQ(glm::vec3(1.f, 100.f, 2.f), ch2.position());
	EXPECT_EQ(float(M_PI*0.25), ch2.direction());
	EXPECT_EQ(10., ch2.maxLife());
	EXPECT_NE(ch2.maxLife(), ch2.life());
	EXPECT_EQ(5.5, ch2.life());
	EXPECT_EQ(1.5f, ch2.speed());
}

TEST(Character, set_position){
	Character ch, ch2;
	ch.position(glm::vec3(1.f, .5f, 2.f));
	EXPECT_NE(ch2.position(), ch.position());
	EXPECT_EQ(glm::vec3(1.f, .5f, 2.f), ch.position());
}

TEST(Character, set_direction){
	Character ch, ch2;
	float x = M_PI*.25;
	ch.direction(x);
	EXPECT_EQ(ch2.position(), ch.position());
	EXPECT_NE(M_PI, ch.direction());
	EXPECT_EQ(x, ch.direction());
}

TEST(Character, rotate_left){
	Character ch;
	EXPECT_EQ(float(M_PI), ch.direction());
	ch.rotateLeft(60.f);
	EXPECT_LT(float(M_PI), ch.direction());
}

TEST(Character, get_direction){
	Character ch, ch2;
	EXPECT_NE(glm::vec3(0.f, 0.f, 0.f), ch.getDirection());
	EXPECT_EQ(glm::vec3(sin(ch.direction()), 0, cos(ch.direction())), ch.getDirection());
	ch.direction(float(M_PI*.25));
	EXPECT_EQ(float(M_PI*.25), ch.direction());
	EXPECT_NEAR(float(sin(float(float(M_PI)*.25f))), ch.getDirection().x, LDBL_EPSILON*1000000000000);
	EXPECT_EQ(float(cos(M_PI*.25)), ch.getDirection().z);
	EXPECT_EQ(0, ch.getDirection().y);
	EXPECT_EQ(ch2.position(), ch.position());
}

TEST(Character, move_front){
	Character ch, ch2;
	ch.rotateLeft(0.5);
	ch.moveFront(1);
	EXPECT_NE(ch2.position(), ch.position());
	EXPECT_GT(ch2.position().x, ch.position().x);
	EXPECT_EQ(ch2.position().y, ch.position().y);
	EXPECT_GT(ch2.position().z, ch.position().z);
	ch.rotateLeft(90.f);
	ch.moveFront(-1);
	ch.moveFront(-1);
	EXPECT_EQ(ch2.position().y, ch.position().y);
	EXPECT_LT(ch2.position().x, ch.position().x);
	EXPECT_GT(ch2.position().z, ch.position().z);
}

TEST(Character, move_left){
	Character ch, ch2;
	ch.moveLeft(1);
	EXPECT_NE(ch2.position(), ch.position());
	EXPECT_LT(ch2.position().x, ch.position().x);
	EXPECT_EQ(ch2.position().y, ch.position().y);
	EXPECT_EQ(ch2.position().z, ch.position().z);
	ch.rotateLeft(60.f);
	ch.moveFront(-1);
	EXPECT_LT(ch2.position().x, ch.position().x);
	EXPECT_EQ(ch2.position().y, ch.position().y);
	EXPECT_LT(ch2.position().z, ch.position().z);
}

TEST(Character, is_jumping){
	Character ch;
	EXPECT_FALSE(ch.isJumping());
	ch.jump();
	EXPECT_TRUE(ch.isJumping());
}

TEST(Character, jump){
	Character ch, ch2;
	EXPECT_EQ(ch2.position(), ch.position());
	EXPECT_FALSE(ch.isJumping());
	ch.jump();
	EXPECT_TRUE(ch.isJumping());
	EXPECT_EQ(ch2.position().x, ch.position().x);
	EXPECT_LT(ch2.position().y, ch.position().y);
	EXPECT_EQ(ch2.position().z, ch.position().z);
}

TEST(Character, gravity){
	Character ch, ch2;
	EXPECT_EQ(ch2.position(), ch.position());
	ch.gravity();
	EXPECT_EQ(ch2.position().x, ch.position().x);
	EXPECT_GT(ch2.position().y, ch.position().y);
	EXPECT_EQ(ch2.position().z, ch.position().z);
}
