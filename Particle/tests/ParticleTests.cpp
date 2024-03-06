#include <gtest/gtest.h>
#include "Particle.h"


TEST(Particle,ctor)
{
  Particle p;
  EXPECT_FLOAT_EQ(p.pos.m_x,0.0f);
  EXPECT_FLOAT_EQ(p.pos.m_y,0.0f);
  EXPECT_FLOAT_EQ(p.pos.m_z,0.0f);

  EXPECT_FLOAT_EQ(p.dir.m_x,0.0f);
  EXPECT_FLOAT_EQ(p.dir.m_y,0.0f);
  EXPECT_FLOAT_EQ(p.dir.m_z,0.0f);

  EXPECT_FLOAT_EQ(p.colour.m_x,0.0f);
  EXPECT_FLOAT_EQ(p.colour.m_y,0.0f);
  EXPECT_FLOAT_EQ(p.colour.m_z,0.0f);
  EXPECT_EQ(p.life,100);
  EXPECT_FLOAT_EQ(p.size,0.01f);
}

TEST(Vec3,ctor)
{
  Vec3 a;
  EXPECT_FLOAT_EQ(a.m_x,0.0f);
  EXPECT_FLOAT_EQ(a.m_y,0.0f);
  EXPECT_FLOAT_EQ(a.m_z,0.0f);

}

TEST(Vec3,userCtor)
{
  Vec3 a(0.1f,0.2f,0.3f);
  EXPECT_FLOAT_EQ(a.m_x,0.1f);
  EXPECT_FLOAT_EQ(a.m_y,0.2f);
  EXPECT_FLOAT_EQ(a.m_z,0.3f);
}


TEST(Particle,userCtor)
{
    // pos, dir , life ,size colour
  auto p = Particle({0.1f,0.2f,0.3f},{0,1,0},200);
  EXPECT_FLOAT_EQ(p.pos.m_x,0.1f);
  EXPECT_FLOAT_EQ(p.pos.m_y,0.2f);
  EXPECT_FLOAT_EQ(p.pos.m_z,0.3f);
  EXPECT_FLOAT_EQ(p.dir.m_x,0.0f);
  EXPECT_FLOAT_EQ(p.dir.m_y,1.0f);
  EXPECT_FLOAT_EQ(p.dir.m_z,0.0f);
  EXPECT_EQ(p.life,200);
}





















