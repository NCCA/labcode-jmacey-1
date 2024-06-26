#include "Emitter.h"
#include "Random.h"
#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include <algorithm>
Emitter::Emitter(int _numParticles, int _maxAlive)
{
  m_particles.resize(_numParticles);
  m_maxAlive=_maxAlive;
  for(auto &p : m_particles)
  {
    createZeroParticle(p);
  }
}

void Emitter::createZeroParticle(Particle &_p)
{
  _p.pos={0,0,0};
  _p.size=0.0f;
  _p.dir={0,0,0};
  _p.isAlive = false;
}

void Emitter::createDefaultParticle(Particle &_p)
{
  _p.pos=m_position;
  _p.dir=m_emitDir * Random::randomPositiveFloat() +
        Random::randomVectorOnSphere() * m_spread;
  _p.dir.m_y = std::abs(_p.dir.m_y);
  _p.colour = Random::randomPositiveVec3();
  _p.life = static_cast<int>(2.0f+Random::randomPositiveFloat(150));
  _p.size= 0.01f;
  _p.isAlive = true;
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
static int numP =0;
// choose number to birth
// find first not alive and set as new particle
int numberToBirth=10+Random::randomPositiveFloat(50);

for(int i=0; i<numberToBirth; ++i)
{
  auto p = std::find_if(std::begin(m_particles),std::end(m_particles),
                        [](auto p)
                        {
                          return p.isAlive==false;
                        });
  createDefaultParticle(*p);
}

  for(auto &p : m_particles)
  {
    if (p.isAlive == true)
    {
      p.dir += gravity * _dt * 0.5;
      p.pos += p.dir * _dt;
      p.size += 0.01f;

      if (--p.life == 0 || p.pos.m_y <= 0.0)
      {
         createZeroParticle(p);
      }
    }
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







