#ifndef WALKER_H_
#define WALKER_H_
#include "Image.h"
#include <memory>
#include <random>
#include <string_view>
class Walker
{
public :
  Walker(int _w, int _h);
  void randomSeed();
  void saveImage(std::string_view _fname) const;
private :
    int m_width;
    int m_height;
    std::unique_ptr<Image> m_map;
    std::uniform_int_distribution<> m_xRand;
    std::uniform_int_distribution<> m_yRand;
    void initRNG();


};


#endif
