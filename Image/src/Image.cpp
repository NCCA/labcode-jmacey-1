#include "Image.h"


Image::Image(int _w, int _h) : m_width{_w},m_height{_h}
{

}

int Image::width() const
{
  return m_width;
}

int Image::height() const
{
  return m_height;
}
