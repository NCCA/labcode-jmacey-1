#include <gtest/gtest.h>
#include "Image.h"


TEST(Image,ctor)
{
  Image img(100,200);

  EXPECT_EQ(img.width(),100);
  EXPECT_EQ(img.height(),200);
}
