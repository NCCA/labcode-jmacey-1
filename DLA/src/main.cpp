#include <iostream>
#include <cstdlib>
#include "Walker.h"

int main()
{
  Walker sim(400,400);
  std::cout<<"DLA Sim\n";
  for(int i=0; i<400; ++i)
  {
//    sim.randomSeed();
      sim.setSeed(i,200);
  }
  sim.saveImage("start.png");
  char name[100];
  int frame=0;
  for(int iteration=0; iteration<10000; ++iteration)
  {
    auto found=sim.walk();
    if(found)
    {
      std::cout<<"Found Seed\n";
      if(iteration % 250)
      {
        std::snprintf(name,100,"img.%04d.png",frame++);
        sim.saveImage(name);
      }
    }

  }


  sim.saveImage("test.png");

  return EXIT_SUCCESS;
}