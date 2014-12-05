/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
 * */

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
    Image& operator=(Image const &img);

    //init the pixel vector and min/max attributes.
    void initImage();

    std::vector<Eigen::Vector4f> pixels() {return m_Pixel;}
    Eigen::Vector4f pixel(unsigned int x, unsigned int y) const {return m_Pixel[x + m_Width*y];}
    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}
    float min() const {return m_Min;}
    float max() const {return m_Max;}

    void setPixel(unsigned int x, unsigned int y, Eigen::Vector4f pixel) {m_Pixel[x + m_Width*y] = pixel;}
    void setHeight(int height) {m_Height = height;}
    void setWidth(int width) {m_Width = width;}
    void setMax(float max) {m_Max = max;}
    void setMin(float min) {m_Min = min;}

    //Compute the min and max value based on the highest and lowest of the RGB channels
    void computeMinMax();

    //Normalize the image pixels using m_Max.
    //computeMinMax() must be called before calling normalize().
    void normalize();

    //Format conversion functions (using cv toolkit).
    void rgb2hsv();
    void hsv2rgb();
    void color2gray();

    //Call this function when an image is loaded.
    void changeNULLStatus(bool status) {imageIsNULL = status;}
    bool isNULL() {return imageIsNULL;}

    IMG_FORMAT format() const {return m_currentFormat;}

private:

    IMG_FORMAT m_currentFormat;
    std::vector<Eigen::Vector4f> m_Pixel;
    unsigned int m_Height;
    unsigned int m_Width;
    float m_Min;
    float m_Max;

    //Initialized to true in constructor
    bool imageIsNULL;

protected:

};

#endif //IMAGE_H_INCLUDED

