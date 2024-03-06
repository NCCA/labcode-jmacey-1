#include <iostream>
#include "Walker.h"


std::mt19937 g_rd;

Walker::Walker(int _w, int _h) : m_width{_w}, m_height{_h}
{
  m_map = std::make_unique<Image>(_w,_h,255,255,255,0);
  initRNG();
}

void Walker::initRNG()
{
  m_xRand=std::uniform_int_distribution<>(1,m_width-1);
  m_yRand=std::uniform_int_distribution<>(1,m_height-1);
}

void Walker::setSeed(int _x, int _y)
{
  m_map->setPixel(_x,_y,255,255,255,255);
}


void Walker::randomSeed()
{
  m_map->setPixel(m_xRand(g_rd),m_yRand(g_rd),255,255,255,255);
}

void Walker::saveImage(std::string_view _fname) const
{
  m_map->save(_fname);
}




bool Walker::walk()
{
  bool found=false;
  // reset start point for walker
  int xpos=m_xRand(g_rd);
  int ypos=m_yRand(g_rd);
  std::uniform_int_distribution<>walkDir(-1,1);
  bool walking = true;
  while(walking)
  {
    xpos+=walkDir(g_rd);
    ypos+=walkDir(g_rd);

    // have I hit the edges?
    if(xpos == 0 || xpos >= m_width-1 || ypos ==0 || ypos >= m_height-1)
    {
      //std::cout<<"hit edge\n";
      found = false;
      walking = false;
      break;
    }
    // search local pixels for an alpha of 0
    RGBA p;
    for(int y=-1; y<=1; ++y)
    {
      for(int x=-1; x<=1; ++x)
      {
        p=m_map->getPixel(xpos+x,ypos+y);
        std::cout<<"alpha is "<<static_cast<int>(p.a)<<'\n';
        if(p.a == 255)
        {
          //std::cout<<"Found seed\n" << xpos+x<<' '<<ypos+y<<'\n';
          m_map->setPixel(xpos,ypos,255,0,0,0);
          found=true;
          walking = false;
          break;
        }
     }
    }

  } // end while walking

  return found;
}

/*

bool Walker::walk()
{
  bool walking=true;
  bool found;
  int m_xpos=m_xRand(g_rd);
  int m_ypos=m_yRand(g_rd);

  while(walking)
  {
    // move walker
    m_xpos += g_walkDir(g_rd);
    m_ypos += g_walkDir(g_rd);
    if(m_xpos == 0 || m_xpos >= m_map->width()-1 ||
       m_ypos == 0 || m_ypos >= m_map->height()-1 )
    {
      walking = false;
      found=false;
      break;
    }

    RGBA p;
    // see if we have a hit
    for(int y=-1; y<=1; ++y )
    {
      for(int x=-1; x<=1; ++x)
      {
        p=m_map->getPixel(m_xpos+x,m_ypos+y);
        if(p.a == 255)
        {
          std::cout<<"found position "<<m_xpos<<' '<<m_ypos<<'\n';
          m_map->setPixel(m_xpos,m_ypos,255,255,255,255);
          walking = false;
          found=true;
          break;
        }
      }
    }

  }
  return found;
}





*/













