#include <iostream>
#include <cstdlib>
#include "Image.h"

int main()
{
  char fname[100];
    Image img(100,100);
    int frame=0;
  for(int x=0; x<100; ++x)
  {
    for(int y=45; y<55; ++y)
      img.setPixel(x,y,255,0,0,255);

    snprintf(fname,100,"frame.%04d.png",frame++);
    img.save(fname);

  }

    std::cout<<"RGBA\n";
    return EXIT_SUCCESS;
}