#ifndef RGBA_H_
#define RGBA_H_
#include <cstdint>
#include <algorithm>

struct RGBA
{
RGBA()=default; 
RGBA(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a=255) :
                            r{_r},g{_g},b{_b},a{_a} {}

void set(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a=255) 
{
    r=_r;
    g=_g;
    b=_b;
    a=_a;    
}

void clamp(unsigned char _low, unsigned char _hi)
{
    r=std::clamp(r,_low,_hi);
    g=std::clamp(g,_low,_hi);
    b=std::clamp(b,_low,_hi);
    a=std::clamp(a,_low,_hi);
}

 union 
 {
    uint32_t pixels=0;
    struct
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
 };
};

#endif