#ifndef EMITTER_H_
#define EMITTER_H_

#include <vector>
#include <string_view>
#include <ngl/Vec3.h>
#include <ngl/MultiBufferVAO.h>
#include <memory>
class Emitter
{
public :
  Emitter(int _numParticles, int _maxAlive);
  void update();
  void render() const;
private :
  ngl::Vec3 randomVectorOnSphere();
  void createDefaultParticle(size_t _p);
  void createZeroParticle(size_t _p);
  size_t m_numParticles;
  ngl::Vec3 m_position={0,0,0};
  float m_spread = 15.0f;
  ngl::Vec3 m_emitDir = {0,20.0f,0};
  int m_maxAlive;
  std::unique_ptr<ngl::MultiBufferVAO> m_vao;

    std::vector<ngl::Vec4> pos;
    std::vector<ngl::Vec3> dir;
    std::vector<ngl::Vec3> colour;
    std::vector<int> life;
    //std::vector<float> size;
    std::vector<bool> isAlive;


};


#endif