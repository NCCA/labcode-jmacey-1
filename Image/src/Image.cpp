#include "Image.h"
#include <algorithm>
#include <OpenImageIO/imageio.h>


Image::Image(int _w, int _h) : m_width{_w},m_height{_h}
{
  m_pixels = std::make_unique<RGBA []>(m_width*m_height);
//  std::fill_n(m_pixels.get(),m_height*m_width,RGBA(255,255,255,255));

  for(size_t i=0; i<m_width*m_height; ++i)
  {
    m_pixels[i]=RGBA(255,255,255,255);
  }
}

int Image::width() const
{
  return m_width;
}

int Image::height() const
{
  return m_height;
}

RGBA Image::getPixel(int _x, int _y) const
{
  // mul row add col
  size_t index = (_y * m_width) + _x;
  //  if( (_x <0 || _x>m_width) || (_y<0 || _y>m_height))
  if ((_x >= 0 && _x <= m_width - 1) && (_y >= 0 && _y <= m_height - 1))
  {
    return m_pixels[index];
  }
  else
  {
    return RGBA(0, 0, 0, 0);
  }
}


void Image::setPixel(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
  size_t index = (_y * m_width) + _x;
  if ((_x >= 0 && _x <= m_width - 1) && (_y >= 0 && _y <= m_height - 1))
    m_pixels[index]=RGBA(_r,_g,_b,_a);
}










bool Image::save(std::string_view _filename)
{
  bool success=false;
  using namespace OIIO;
  auto out = ImageOutput::create(_filename.data());
  if(!out)
  {
    return false;
  }
  ImageSpec spec(m_width,m_height,4,TypeDesc::UINT8);
  success = out->open(_filename.data(),spec);
  success = out->write_image(TypeDesc::UINT8,m_pixels.get());
  success = out->close();
  return success;
}














