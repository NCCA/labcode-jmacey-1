#include <iostream>
#include <cstdlib>
#include "Walker.h"

int main()
{
  Walker sim(400,400);
  std::cout<<"DLA Sim\n";
  for(int i=0; i<40; ++i)
  {
    sim.randomSeed();
  }
  char name[100];
  int frame=0;
  for(int iteration=0; iteration<10000; ++iteration)
  {
    auto found=sim.walk();
    if(found)
    {
      std::snprintf(name,100,"img.%04d.bmp",frame++);
      sim.saveImage(name);

      std::cout<<"Found seed\n";
    }
    else
    {
      std::cout<<"reset\n";
    }
  }



  sim.saveImage("test.bmp");

  return EXIT_SUCCESS;
}