#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>

class Image
{
public :
    Image();

    ~Image();

    Image(QImage img);

    void initImage(int height = m_Height, int width = m_Width){m_Img.reserve(height*width);}

    Eigen::Vector3f pixel(int x, int y) const {return m_Img[x + m_Width*y];}
    int height() const {return m_Height;}
    int width() const {return m_Width;}
    float min() const {return m_Min;}
    float max() const {return m_Max;}

    void setPixel(int x, int y, Eigen::Vector3f pixel) {m_Img[x + m_Width*y] = pixel;}
    void setHeight(int height) {m_Height = height;}
    void setWidth(int width) {m_Width = width;}
    void setMax(float max) {m_Max = max;}
    void setMin(float min) {m_Min = min;}

private:

    std::vector<Eigen::Vector3f> m_Img;
    int m_Height;
    int m_Width;
    int m_Min;
    int m_Max;

protected:

};

#endif IMAGE_H
