#include <iostream>
#include "Walker.h"



std::mt19937 g_rd;

Walker::Walker(int _w, int _h) : m_width{_w}, m_height{_h}
{
  m_map = std::make_unique<Image>(_w,_h,255,255,255,255);
  initRNG();
}

void Walker::initRNG()
{
  m_xRand=std::uniform_int_distribution<>(1,m_width-1);
  m_yRand=std::uniform_int_distribution<>(1,m_height-1);
}

void Walker::setSeed(int _x, int _y)
{
  m_map->setPixel(_x,_y,255,0,0,0);
}


void Walker::randomSeed()
{
  m_map->setPixel(m_xRand(g_rd),m_yRand(g_rd),255,0,0,0);
}

void Walker::saveImage(std::string_view _fname) const
{
  m_map->save(_fname);
}




bool Walker::walk()
{
  std::uniform_int_distribution<>walkDir(-1,1);

  bool found=false;
  // reset start point for walker
  int xpos=m_xRand(g_rd);
  int ypos=m_yRand(g_rd);
  while(true)
  {
    xpos+=walkDir(g_rd);
    ypos+=walkDir(g_rd);

    // have I hit the edges?
    if(xpos == 0 || xpos >= m_width-1 || ypos ==0 || ypos >= m_height-1)
    {
     found = false;
     goto finished;
    }
    // search local pixels for an alpha of 0
    RGBA p;
    for(int y=-1; y<=1; ++y)
    {
      for(int x=-1; x<=1; ++x)
      {
        p=m_map->getPixel(xpos+x,ypos+y);
        if(p.a == 0)
        {
          m_map->setPixel(xpos,ypos,0,0,0,0);
          found=true;
          goto finished;
        }
     }
    }

  } // end while walking
  finished :
    return found;
}








