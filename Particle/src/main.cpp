#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
int main()
{
  std::cout<<"Particle System\n";
  Emitter e(10000,500);
  for(int i=0; i<250; ++i)
  {
    //std::cout<<"Frame "<<i<<'\n';
    e.update();
 //   e.render();
    e.writeToGeo(fmt::format("particle.{:04d}.geo",i));
  }

  return EXIT_SUCCESS;
}