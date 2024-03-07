#include "Vec3.h"


Vec3 & Vec3::operator+=(const Vec3 &_rhs)
{
  m_x+=_rhs.m_x;
  m_y+=_rhs.m_y;
  m_z+=_rhs.m_z;
  return *this;
}

Vec3 Vec3::operator *(float _rhs) const
{
  return Vec3(m_x*_rhs, m_y *_rhs, m_z*_rhs);
}

Vec3 Vec3::operator+(const Vec3 &_rhs) const
{
  return Vec3(m_x+_rhs.m_x,m_y + _rhs.m_y,
              m_z + _rhs.m_z);
}