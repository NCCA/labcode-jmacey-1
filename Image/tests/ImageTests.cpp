#include <gtest/gtest.h>
#include "Image.h"
#include "RGBA.h"

TEST(Image,ctor)
{
  Image img(100,200);
  EXPECT_EQ(img.width(),100);
  EXPECT_EQ(img.height(),200);
  auto pixel=img.getPixel(10,10);
  EXPECT_EQ(pixel.r,255);
  EXPECT_EQ(pixel.g,255);
  EXPECT_EQ(pixel.b,255);
  EXPECT_EQ(pixel.a,255);
}

TEST(Image,GetPixel)
{
  Image img(10,10);
  {
    auto pixel=img.getPixel(-1,-1);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,0);
  }
  {
    auto pixel=img.getPixel(3,4);
    EXPECT_EQ(pixel.r,255);
    EXPECT_EQ(pixel.g,255);
    EXPECT_EQ(pixel.b,255);
    EXPECT_EQ(pixel.a,255);
  }
  {
    auto pixel=img.getPixel(10,10);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,0);
  }
}

TEST(Image,setPixel)
{
  Image img(1,3);
  img.setPixel(0,0,255,0,0,255);
  auto pixel = img.getPixel(0,0);
  EXPECT_EQ(pixel.r,255);
  EXPECT_EQ(pixel.g,0);
  EXPECT_EQ(pixel.b,0);
  EXPECT_EQ(pixel.a,255);

}