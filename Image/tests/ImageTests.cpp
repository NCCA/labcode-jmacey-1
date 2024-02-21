#include <gtest/gtest.h>
#include "Image.h"
#include "RGBA.h"

TEST(Image,ctor)
{
  Image img(100,200);
  EXPECT_EQ(img.width(),100);
  EXPECT_EQ(img.height(),200);
  auto pixel=img.getPixel(0,0);
  EXPECT_EQ(pixel.r,255);
  EXPECT_EQ(pixel.g,255);
  EXPECT_EQ(pixel.b,255);
  EXPECT_EQ(pixel.a,255);


}
