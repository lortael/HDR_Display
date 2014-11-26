#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <vector>
#include <Eigen/Core>

enum IMG_FORMAT {RGB = 1, HSV = 2, GRAY = 0};

class Image
{
public :
    Image();

    Image(Image const &img);

    ~Image();

    void initImage();

    std::vector<Eigen::Vector4f> pixels() {return m_Pixel;}

    Eigen::Vector4f pixel(unsigned int x, unsigned int y) const {return m_Pixel[x + m_Width*y];}
    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}
    Eigen::Vector3f min() const {return m_Min;}
    Eigen::Vector3f max() const {return m_Max;}

    void setPixel(unsigned int x, unsigned int y, Eigen::Vector4f pixel) {m_Pixel[x + m_Width*y] = pixel;}
    void setHeight(int height) {m_Height = height;}
    void setWidth(int width) {m_Width = width;}
    void setMax(Eigen::Vector3f max) {m_Max = max;}
    void setMin(Eigen::Vector3f min) {m_Min = min;}

    void rgb2hsv();
    void hsv2rgb();
    void color2gray();

    Image& operator=(Image const &img);

    void changeNULLStatus(bool status) {imageIsNULL = status;}
    bool isNULL() {return imageIsNULL;}

    IMG_FORMAT format() {return m_currentFormat;}

private:

    IMG_FORMAT m_currentFormat;
    std::vector<Eigen::Vector4f> m_Pixel;
    unsigned int m_Height;
    unsigned int m_Width;
    Eigen::Vector3f m_Min;
    Eigen::Vector3f m_Max;
    bool imageIsNULL;

protected:

};

#endif //IMAGE_H_INCLUDED

