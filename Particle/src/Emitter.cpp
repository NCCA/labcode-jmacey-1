#include "Emitter.h"
#include "Random.h"
#include <fmt/format.h>
#include <iostream>
#include <fstream>
Emitter::Emitter(int _numParticles)
{
  m_particles.resize(_numParticles);
  for(auto &p : m_particles)
  {
    p.pos=m_position;
    p.dir=m_emitDir * Random::randomPositiveFloat() +
      Random::randomVectorOnSphere() * m_spread;
    p.dir.m_y = std::abs(p.dir.m_y);
  }
}

void Emitter::render() const
{
  for(auto p : m_particles)
  {
    fmt::print("{} ,{}, {} \n",p.pos.m_x,
               p.pos.m_y, p.pos.m_z);
  }
}

void Emitter::update()
{
// dir += gravity * _dt * 0.5f
//  pos += p.dir * _dt
float _dt=0.1f;
Vec3 gravity(0,-9.87, 0);
  for(auto &p : m_particles)
  {
    p.dir += gravity * _dt *0.5;
    p.pos += p.dir *_dt;
  }
}
void Emitter::writeToGeo(std::string_view _fname)
{
  std::cout<<"writing "<<_fname<<'\n';
  auto file = std::ofstream(_fname.data());
  if(file.is_open())
  {
    file<<"PGEOMETRY V5\n";
    file << "NPoints "<< m_particles.size() << " NPrims 0 \n";
    file << "NPointGroups 0 NPrimGroups 0 \n";
    file << "NPointAttrib 2 NVertexAttrib 1 NAttrib 0\n";
    file << "PointAttrib \n";
    file << "Cd 3 float 0 0 0\n";
    file << "pscale 1 float 0.1 \n";
  }
}







