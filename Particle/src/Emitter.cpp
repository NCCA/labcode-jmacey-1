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
    p.colour = Random::randomPositiveVec3();
    p.life = static_cast<int>(2.0f+Random::randomPositiveFloat(50));
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
    if(--p.life == 0 || p.pos.m_y <= 0.0)
    {
      p.pos={0,0,0};
      p.size=0.1;
      p.dir = m_emitDir * Random::randomPositiveFloat() +
              Random::randomVectorOnSphere() * m_spread;
      p.life = static_cast<int>(2.0f+Random::randomPositiveFloat(50));
    }
    p.dir += gravity * _dt *0.5;
    p.pos += p.dir *_dt;
    p.size+=0.1f;

  }
}
void Emitter::writeToGeo(std::string_view _fname)
{
  std::cout<<"writing "<<_fname<<'\n';
  auto file = std::ofstream(_fname.data());
  if(file.is_open())
  {
    file<<"PGEOMETRY V5\n";
    file << "NPoints "<< m_particles.size() << " NPrims 1 \n";
    file << "NPointGroups 0 NPrimGroups 0 \n";
    file << "NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 1 NAttrib 0\n";
    file << "PointAttrib \n";
    file << "Cd 3 float 0 0 0\n";
    file << "pscale 1 float 0.1 \n";
    for(auto p : m_particles)
    {
      file << p.pos.m_x <<' '<<p.pos.m_y<<' '<<p.pos.m_z<<' '<<" 1 (";
      file<<p.colour.m_x<<' '<<p.colour.m_y<<' '<<p.colour.m_z<<' ';
      file<< p.size<<' ';
      file<<")\n";
    } // end of per particle data
    file << "PrimitiveAttrib \n";
    file << "generator 1 index 1 papi \n";
    file << "Part ";
    file << m_particles.size()<<' ';
    for(size_t i=0; i<m_particles.size(); ++i)
      file<< i<<' ';
    file <<"[0] \n";
    file<<"beginExtra\nendExtra\n";
  }
}







