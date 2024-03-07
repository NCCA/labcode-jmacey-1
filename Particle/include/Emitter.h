#ifndef EMITTER_H_
#define EMITTER_H_

#include <vector>
#include <string_view>
#include "Particle.h"
#include "Vec3.h"

class Emitter
{
public :
  Emitter(int _numParticles);
  void update();
  void render() const;
  void writeToGeo(std::string_view _fname);
private :
  std::vector<Particle> m_particles;
  Vec3 m_position={0,0,0};
  float m_spread = 15.0f;
  Vec3 m_emitDir = {0,20.0f,0};
};


#endif