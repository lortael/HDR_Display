/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Class to handle HDR images (based on float data points). *
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
    float minRGB() const {return m_MinRGB;}
    float maxRGB() const {return m_MaxRGB;}
    float minHSL() const {return m_MinHSL;}
    float maxHSL() const {return m_MaxHSL;}

    void setPixel(unsigned int x, unsigned int y, Eigen::Vector4f pixel) {m_Pixel[x + m_Width*y] = pixel;}
    void setHeight(int height) {m_Height = height;}
    void setWidth(int width) {m_Width = width;}
    void setMaxRGB(float max) {m_MaxRGB = max;}
    void setMinRGB(float min) {m_MinRGB = min;}
    void setMaxHSL(float max) {m_MaxHSL = max;}
    void setMinHSL(float min) {m_MinHSL = min;}
    void setFormat(IMG_FORMAT format) {m_currentFormat = format;}

    //Call the two private functions (computeAbsoluteMinMax, computeHSLMinMax) to compute all min/max.
    void computeMinMax();

    //Normalize the RGB image pixels using m_MaxRGB.
    //computeMinMax() must be called before calling normalize().
    void normalizeRGB();

    //Format conversion functions (using cv toolkit).
    void rgb2hsv();
    void hsv2rgb();
    void color2gray();

    //CPU tone-mapping, to be used only with CPU-based displaying process.
    void toneMapping();

    //Call this function when an image is loaded (already done in ImageIO).
    void changeNULLStatus(bool status) {imageIsNULL = status;}
    bool isNULL() {return imageIsNULL;}

    IMG_FORMAT format() const {return m_currentFormat;}

private:

    //Compute the min and max value based on the highest and lowest of the RGB channels.
    void computeAbsoluteMinMax();
    //Compute the min and max value based on the highest and lowest value for the V channel in HSV format.
    void computeHSLMinMax();

    IMG_FORMAT m_currentFormat;
    std::vector<Eigen::Vector4f> m_Pixel;
    unsigned int m_Height;
    unsigned int m_Width;
    float m_MinRGB;
    float m_MaxRGB;
    float m_MinHSL;
    float m_MaxHSL;

    //Initialized to true in constructor
    bool imageIsNULL;

protected:

};

#endif //IMAGE_H_INCLUDED

