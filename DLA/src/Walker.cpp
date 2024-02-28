#include "Walker.h"

std::mt19937 g_rd;

Walker::Walker(int _w, int _h) : m_width{_w}, m_height{_h}
{
  m_map = std::make_unique<Image>(_w,_h);
  initRNG();
}

void Walker::initRNG()
{
  m_xRand=std::uniform_int_distribution<>(1,m_width-1);
  m_yRand=std::uniform_int_distribution<>(1,m_height-1);
}

void Walker::randomSeed()
{
  m_map->setPixel(m_xRand(g_rd),m_yRand(g_rd),255,0,0,255);
}

void Walker::saveImage(std::string_view _fname) const
{
  m_map->save(_fname);
}