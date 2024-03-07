#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
int main()
{
  std::cout<<"Particle System\n";
  Emitter e(100);
  for(int i=0; i<10; ++i)
  {
    //std::cout<<"Frame "<<i<<'\n';
    e.update();
    e.render();
    e.writeToGeo(fmt::format("particle.{:04d}.geo",i));
  }

  return EXIT_SUCCESS;
}