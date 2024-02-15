#include <gtest/gtest.h>
#include "RGBA.h"

TEST(RGBA,construct)
{
    RGBA pixel;
    ASSERT_TRUE(pixel.r == 0);
    ASSERT_TRUE(pixel.g == 0);
    ASSERT_TRUE(pixel.b == 0);
    ASSERT_TRUE(pixel.a == 0);
}

TEST(RGBA,constructUser)
{
    RGBA pixel(255,128,54,0);
    ASSERT_TRUE(pixel.r == 255);
    ASSERT_TRUE(pixel.g == 128);
    ASSERT_TRUE(pixel.b == 54);
    ASSERT_TRUE(pixel.a == 0);

    RGBA pixel2(64,22,32);
    ASSERT_TRUE(pixel2.r == 64);
    ASSERT_TRUE(pixel2.g == 22);
    ASSERT_TRUE(pixel2.b == 32);
    ASSERT_TRUE(pixel2.a == 255);
}

TEST(RGBA,set)
{
    RGBA pixel;
    ASSERT_EQ(pixel.r , 0);
    ASSERT_EQ(pixel.g , 0);
    ASSERT_EQ(pixel.b , 0);
    ASSERT_EQ(pixel.a , 0);
    pixel.set(255,255,255,255);
    ASSERT_EQ(pixel.r , 255);
    ASSERT_EQ(pixel.g , 255);
    ASSERT_EQ(pixel.b , 255);
    ASSERT_EQ(pixel.a , 255);
}

TEST(RGBA,clamp)
{
    auto pixel=RGBA(255,128,54,22);
    pixel.clamp(35,240);
    ASSERT_EQ(pixel.r,240);
    ASSERT_EQ(pixel.g,128);
    ASSERT_EQ(pixel.b,54);
    ASSERT_EQ(pixel.a,35);
    
    
    
}