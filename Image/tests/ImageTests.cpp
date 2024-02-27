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

TEST(Image,ctorRGBA)
{
    int width=10;
    int height=20;
    Image img(width,height,255,128,0,128);
    EXPECT_EQ(img.width(),width);
    EXPECT_EQ(img.height(),height);
    for(int y=0; y<height; ++y)
    {
        for(int x=0; x<width; ++x)
        {
            auto pixel=img.getPixel(x,y);
            EXPECT_EQ(pixel.r,255);
            EXPECT_EQ(pixel.g,128);
            EXPECT_EQ(pixel.b,0);
            EXPECT_EQ(pixel.a,128);
        }
    }

}

TEST(Image,clear)
{
    Image img(10,10);
    img.clear(255,0,0,255);
    for(int y=0; y<10; ++y)
    {
        for(int x=0; x<10; ++x)
        {
        auto pixel=img.getPixel(x,y);
        EXPECT_EQ(pixel.r,255);
        EXPECT_EQ(pixel.g,0);
        EXPECT_EQ(pixel.b,0);
        EXPECT_EQ(pixel.a,255);
        }
    }

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

TEST(Image,setPixelRGBA)
{
  Image img(1,3);
  img.setPixel(0,0,RGBA(255,0,0,255));
  auto pixel = img.getPixel(0,0);
  EXPECT_EQ(pixel.r,255);
  EXPECT_EQ(pixel.g,0);
  EXPECT_EQ(pixel.b,0);
  EXPECT_EQ(pixel.a,255);

}

TEST(IMAGE,line)
{
    Image a(200,200);

    a.line(0,100,200,100,255,0,0,255);
    RGBA p;
    for(size_t x=0; x<a.width(); ++x)
    {
        p=a.getPixel(x,100);
        ASSERT_EQ(p.r,255);
        ASSERT_EQ(p.g,0);
        ASSERT_EQ(p.b,0);
        ASSERT_EQ(p.a,255);

    }
    ASSERT_TRUE(a.save("line1.png"));

}