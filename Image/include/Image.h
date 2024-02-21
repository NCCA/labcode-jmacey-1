#ifndef IMAGE_H_
#define IMAGE_H_

class Image
{
public :
    Image(int _w, int _h);
    [[nodiscard]] int width() const ;
    [[nodiscard]] int height() const ;

private :
    int m_width=0;
    int m_height=0;

};

#endif