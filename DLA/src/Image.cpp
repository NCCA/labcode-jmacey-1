#include "Image.h"
#include <algorithm>
#include <OpenImageIO/imageio.h>

Image::Image(int _w, int _h, unsigned char _r, unsigned char _g, unsigned char _b,unsigned char _a) : m_width{_w},m_height{_h}
{
    m_pixels = std::make_unique<RGBA []>(m_width*m_height);
    for(size_t i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i]=RGBA(_r,_g,_b,_a);
    }
}

Image::Image(int _w, int _h) : Image(_w,_h,255,255,255,255)
{
}

void Image::setPixel(int _x, int _y, const RGBA &_rgba)
{
    size_t index = (_y * m_width) + _x;
    if ((_x >= 0 && _x <= m_width - 1) && (_y >= 0 && _y <= m_height - 1))
        m_pixels[index]=_rgba;

}

void Image::clear(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
    for(size_t i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i]=RGBA(_r,_g,_b,_a);
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



// based on https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void Image::line(int _sx, int _sy, int _ex, int _ey, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a  )
{
    int dx = std::abs(_ex - _sx);
    int dy = std::abs(_ey - _sy);
    int sx = (_sx < _ex) ? 1 : -1;
    int sy = (_sy < _ey) ? 1 : -1;
    int err = dx - dy;
    int x = _sx;
    int y = _sy;
    while (true)
    {
        setPixel(x, y, _r, _g, _b, _a);
        if (x == _ex && y == _ey)
        {
            break; // finished drawing
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
          err -= dy;
          x += sx;
        }
        if (e2 < dx)
        {
          err += dx;
          y += sy;
        }
    }
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














