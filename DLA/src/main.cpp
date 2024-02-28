#include <iostream>
#include <cstdlib>
#include "Walker.h"

int main()
{
  Walker sim(100,100);
  std::cout<<"DLA Sim\n";
  for(int i=0; i<100; ++i)
  {
    sim.randomSeed();
  }
  sim.saveImage("test.png");

  return EXIT_SUCCESS;
}