#include "Emitter.h"
#include <ngl/Random.h>
#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ngl/Util.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
Emitter::Emitter(int _numParticles, int _maxAlive)
{
  m_particles.resize(_numParticles);
  m_maxAlive=_maxAlive;
  for(auto &p : m_particles)
  {
    createZeroParticle(p);
  }
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
}

void Emitter::createZeroParticle(Particle &_p)
{
  _p.pos.set(0.0f,0.0f,0.0f);
  _p.size=0.0f;
  _p.dir.set(0,0,0);
  _p.isAlive = false;
}

void Emitter::createDefaultParticle(Particle &_p)
{
  _p.pos=m_position;
  _p.dir=m_emitDir * ngl::Random::randomPositiveNumber() +randomVectorOnSphere() * m_spread;
  _p.dir.m_y = std::abs(_p.dir.m_y);
  _p.colour = ngl::Random::getRandomColour3();
  _p.life = static_cast<int>(2.0f+ngl::Random::randomPositiveNumber(150));
  _p.size= 0.01f;
  _p.isAlive = true;
}

ngl::Vec3 Emitter::randomVectorOnSphere()
{
  auto phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
  auto costheta = ngl::Random::randomNumber();
  auto theta = acosf(costheta);
  auto u = ngl::Random::randomPositiveNumber();
  auto r = 1.0f *std::cbrt(u);
  return ngl::Vec3(r*sinf(theta) *cosf(phi),
                   r* sinf(theta) * sinf(phi),
                   r*cosf(theta));
}

void Emitter::render() const
{
//  ngl::Mat4 look=ngl::lookAt({0,130,130},{0,0,0},{0,1,0});
//  ngl::Mat4 persp=ngl::perspective(45.0f,1.0,0.1,200);
//  glPointSize(4);
//  ngl::ShaderLib::setUniform("MVP", persp*look);
  m_vao->bind();
  m_vao->setData(ngl::AbstractVAO::VertexData(m_particles.size()*sizeof(Particle),m_particles[0].pos.m_x));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);

  m_vao->setNumIndices(m_particles.size());
  m_vao->draw();
  m_vao->unbind();
  //  ngl::Transformation tx;
//  for(auto p : m_particles)
//  {
//    tx.setPosition(p.pos);
//    tx.setScale(p.size,p.size,p.size);
//    ngl::ShaderLib::setUniform("MVP", persp*look*tx.getMatrix());
//    ngl::ShaderLib::setUniform("Colour",p.colour.m_r,p.colour.m_g,p.colour.m_b,1.0f);
//    ngl::VAOPrimitives::draw(ngl::bunny);//"sphere");
//    //    fmt::print("{} ,{}, {} \n",p.pos.m_x,
////               p.pos.m_y, p.pos.m_z);
//
//
//
//  }
}

void Emitter::update()
{
  //std::cout<<"update\n";
// dir += gravity * _dt * 0.5f
//  pos += p.dir * _dt
float _dt=0.1f;
ngl::Vec3 gravity(0,-9.87, 0);
static int numP =0;
// choose number to birth
// find first not alive and set as new particle
int numberToBirth=1000+ngl::Random::randomPositiveNumber(50);

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







