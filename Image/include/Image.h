#ifndef IMAGE_H_
#define IMAGE_H_

#include "RGBA.h"
#include <memory>
#include <string_view>

class Image
{
public :
    Image(int _w, int _h);
    [[nodiscard]] int width() const ;
    [[nodiscard]] int height() const ;
    [[nodiscard]] RGBA getPixel(int _x, int _y) const;
    void setPixel(int _x, int _y, unsigned char _r,
                  unsigned char _g, unsigned char _b,
                  unsigned char _a=255);
    bool save(std::string_view _filename);
private :
    int m_width=0;
    int m_height=0;
    std::unique_ptr<RGBA []> m_pixels;

};

#endif