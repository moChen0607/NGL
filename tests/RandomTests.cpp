#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec4.h>
#include <ngl/Random.h>
#include <string>
#include <sstream>
#include <glm/vec4.hpp>





TEST(Random,instance)
{
    auto rng=ngl::Random::instance();
    EXPECT_TRUE(rng!=nullptr);
}


TEST(Random,vec2)
{
    auto rng=ngl::Random::instance();
    rng->setSeed();
    auto v=rng->getRandomVec2();
    EXPECT_TRUE(v.m_x>=-1.0f && v.m_x<=1.0f);
    EXPECT_TRUE(v.m_y>=-1.0f && v.m_y<=1.0f);
}


TEST(Random,vec3)
{
    auto rng=ngl::Random::instance();
    rng->setSeed();
    auto v=rng->getRandomVec3();
    EXPECT_TRUE(v.m_x>=-1.0f && v.m_x<=1.0f);
    EXPECT_TRUE(v.m_y>=-1.0f && v.m_y<=1.0f);
    EXPECT_TRUE(v.m_z>=-1.0f && v.m_z<=1.0f);
}


TEST(Random,vec4)
{
    auto rng=ngl::Random::instance();
    rng->setSeed();
    auto v=rng->getRandomVec4();
    EXPECT_TRUE(v.m_x>=-1.0f && v.m_x<=1.0f);
    EXPECT_TRUE(v.m_y>=-1.0f && v.m_y<=1.0f);
    EXPECT_TRUE(v.m_z>=-1.0f && v.m_z<=1.0f);
    EXPECT_TRUE(v.m_w>=-1.0f && v.m_w<=1.0f);
}


TEST(Random,addIntGenerator)
{
    auto rng=ngl::Random::instance();
    rng->setSeed();
    auto dist=std::uniform_int_distribution<int>(-100,100);
    rng->addIntGenerator("test",dist);
    auto test=rng->getIntFromGeneratorName("test");
    EXPECT_TRUE(test>=-100 && test <=100);
}


TEST(Random,addFloatGenerator)
{
    auto rng=ngl::Random::instance();
    rng->setSeed();
    auto dist=std::uniform_real_distribution<float>(0.0f,5.0f);
    rng->addFloatGenerator("test",dist);
    auto test=rng->getFloatFromGeneratorName("test");
    EXPECT_TRUE(test>=0.0f && test <=5.0f);
}

