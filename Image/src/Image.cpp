#include "Image.h"


Image::Image(int _w, int _h) : m_width{_w},m_height{_h}
{
  m_pixels = std::make_unique<RGBA []>(m_width*m_height);
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
  return m_pixels[0];
}