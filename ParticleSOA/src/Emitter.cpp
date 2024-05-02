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
  m_numParticles=_numParticles;
  m_maxAlive=_maxAlive;
  pos.resize(m_numParticles);
  dir.resize(m_numParticles);
  colour.resize(m_numParticles);
  life.resize(m_numParticles);
  isAlive.resize(m_numParticles);
  for(size_t i=0; i<m_numParticles; ++i)
  {
    createZeroParticle(i);
  }
  //  m_particles.resize(_numParticles);
//  m_maxAlive=_maxAlive;
//  for(auto &p : m_particles)
//  {
//    createZeroParticle(p);
//  }
//  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
    m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>(ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_POINTS));
    m_vao->bind();
    m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // positions
    m_vao->setData(ngl::MultiBufferVAO::VertexData(1,0)); // colours
    m_vao->unbind();
}

void Emitter::createZeroParticle(size_t _p)
{
  pos[_p].set(0.0f,0.0f,0.0f,0.01f);
  dir[_p].set(0.0f,0.0f,0.0f);
  isAlive[_p]=false;
}

void Emitter::createDefaultParticle(size_t _p)
{
  pos[_p]=m_position;
  dir[_p]=m_emitDir * ngl::Random::randomPositiveNumber() +randomVectorOnSphere() * m_spread;
  dir[_p].m_y = std::abs(dir[_p].m_y);
  colour[_p] = ngl::Random::getRandomColour3();
  life[_p] = static_cast<int>(2.0f+ngl::Random::randomPositiveNumber(150));
  pos[_p].m_w= 0.01f;
  isAlive[_p] = true;
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
  glEnable(GL_PROGRAM_POINT_SIZE);
  m_vao->bind();
  m_vao->setData(0,ngl::AbstractVAO::VertexData(m_numParticles*sizeof(ngl::Vec4),pos[0].m_x));
  m_vao->setVertexAttributePointer(0,4,GL_FLOAT,0,0);

  m_vao->setData(1,ngl::AbstractVAO::VertexData(m_numParticles*sizeof(ngl::Vec3),colour[0].m_x));
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);
  m_vao->setNumIndices(m_numParticles);
  m_vao->draw();
  m_vao->unbind();
  glDisable(GL_PROGRAM_POINT_SIZE);
}

void Emitter::update()
{
//  //std::cout<<"update\n";
//// dir += gravity * _dt * 0.5f
////  pos += p.dir * _dt
float _dt=0.1f;
ngl::Vec3 gravity(0,-9.87, 0);
//static int numP =0;
//// choose number to birth
// find first not alive and set as new particle
int numberToBirth=1000+ngl::Random::randomPositiveNumber(50);

for(int i=0; i<numberToBirth; ++i)
{
 size_t index=0;
 for(auto a : isAlive )
 {
   if (!a)
     break;
   else
     ++index;
 }
  createDefaultParticle(index);
}

  for(size_t p=0; p<m_numParticles; ++p)
  {
    if(isAlive[p])
    {
      dir[p] += gravity * _dt *0.5f;
      // pos[p].xyz += dir[p] * dt
      // pos[p].x += dir[p].x *dt;
      pos[p] += dir[p] * _dt;
      pos[p].m_w += 0.1f;
      if(--life[p] ==0 || pos[p].m_y <=0.0f)
      {
        createZeroParticle(p);
      }
    }
  }
}
