#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vec3.h"

struct Particle
{
  Particle()=default;

  Particle(Vec3 _pos, Vec3 _dir, int _life, float _size=0.1f, Vec3 _colour={1,1,1}) :
      pos{_pos},dir{_dir},life{_life},size{_size},colour{_colour}
      {

      }

  Vec3 pos;
  Vec3 dir;
  Vec3 colour;
  int life=100;
  float size=0.01f;
};


#endif