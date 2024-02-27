#ifndef IMAGE_H_
#define IMAGE_H_

#include "RGBA.h"
#include <memory>
#include <string_view>

class Image
{
public :
    Image(int _w, int _h);
    Image(int _w, int _h, unsigned char _r, unsigned char _g, unsigned char _b,unsigned char _a=255);
    [[nodiscard]] int width() const ;
    [[nodiscard]] int height() const ;
    void clear(unsigned char _r, unsigned char _g, unsigned char _b,unsigned char _a=255);
    [[nodiscard]] RGBA getPixel(int _x, int _y) const;
    void setPixel(int _x, int _y, unsigned char _r,
                  unsigned char _g, unsigned char _b,
                  unsigned char _a=255);
    void setPixel(int _x, int _y, const RGBA& _rgba);
    bool save(std::string_view _filename);
    void line(int _sx, int _sy, int _ex, int _ey, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a  ) ;

private :
    int m_width=0;
    int m_height=0;
    std::unique_ptr<RGBA []> m_pixels;

};

#endif