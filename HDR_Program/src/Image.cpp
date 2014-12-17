#include "Image.h"
#include <iostream>


#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;


Image::Image()
    : m_Width(0),
      m_Height(0),
      m_currentFormat(RGB),
      imageIsNULL(true),
      m_MaxRGB(0.f),
      m_MaxXYZ(0.f),
      m_MinRGB(250.f),
      m_MinXYZ(250.f)
{
}

Image::Image(Image const &img)
{
    m_Width = img.m_Width;
    m_Height = img.m_Height;
    m_MinRGB = img.m_MinRGB;
    m_MaxRGB = img.m_MaxRGB;
    m_MinXYZ = img.m_MinXYZ;
    m_MaxXYZ = img.m_MaxXYZ;
    m_currentFormat = img.m_currentFormat;
    imageIsNULL = img.imageIsNULL;

    m_Pixel = img.m_Pixel;
}

Image::Image(unsigned int height, unsigned int width)
{
    m_Width = width;
    m_Height = height;
    m_Pixel.resize(m_Height*m_Width);
}

Image::~Image()
{

}

Image& Image::operator=(Image const & img)
{
    m_Width = img.m_Width;
    m_Height = img.m_Height;
    m_MinRGB = img.m_MinRGB;
    m_MaxRGB = img.m_MaxRGB;
    m_MinXYZ = img.m_MinXYZ;
    m_MaxXYZ = img.m_MaxXYZ;
    m_currentFormat = img.m_currentFormat;
    imageIsNULL = img.imageIsNULL;

    m_Pixel = img.m_Pixel;

    return *this;
}

void Image::initImage()
{
    if (m_Pixel.size() != 0)
    {
        m_Pixel.clear();
    }
    m_Pixel.resize(m_Height*m_Width);
}

void Image::rgb2hsv()
{
    if (m_currentFormat == RGB)
    {
        Mat rgbImg(m_Height, m_Width, DataType<Vec3f>::type);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                Vec3f rgb = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                rgbImg.at<Vec3f>(y, x) = rgb; //Inversion of x and y, as opencv deals with image that way.
            }
        }

        Mat hsvImg(m_Height, m_Width, DataType<Vec3f>::type);
        cvtColor(rgbImg, hsvImg, CV_RGB2HSV);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                float h = hsvImg.at<Vec3f>(y, x)(0); //Inversion of x and y, as opencv deals with image that way.
                float s = hsvImg.at<Vec3f>(y, x)(1);
                float v = hsvImg.at<Vec3f>(y, x)(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(h, s, v, 1.f);
            }
        }
        m_currentFormat = HSV;
    }
}

void Image::hsv2rgb()
{
    if (m_currentFormat == HSV)
    {
        Mat hsvImg(m_Height, m_Width, DataType<Vec3f>::type);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                Vec3f hsv = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                hsvImg.at<Vec3f>(y, x) = hsv; //Inversion of x and y, as opencv deals with image that way.
            }
        }
        Mat rgbImg;
        cvtColor(hsvImg, rgbImg, CV_HSV2RGB);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                float r = rgbImg.at<Vec3f>(y, x)(0); //Inversion of x and y, as opencv deals with image that way.
                float g = rgbImg.at<Vec3f>(y, x)(1);
                float b = rgbImg.at<Vec3f>(y, x)(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(r, g, b, 1.f);
            }
        }
        m_currentFormat = RGB;
    }
}

void Image::rgb2xyz()
{
    if (m_currentFormat == RGB)
    {
        Mat rgbImg(m_Height, m_Width, DataType<Vec3f>::type);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                Vec3f rgb = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                rgbImg.at<Vec3f>(y, x) = rgb; //Inversion of x and y, as opencv deals with image that way.
            }
        }

        Mat xyzImg(m_Height, m_Width, DataType<Vec3f>::type);
        cvtColor(rgbImg, xyzImg, CV_RGB2XYZ);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                float x2 = xyzImg.at<Vec3f>(y, x)(0); //Inversion of x and y, as opencv deals with image that way.
                float y2 = xyzImg.at<Vec3f>(y, x)(1);
                float z2 = xyzImg.at<Vec3f>(y, x)(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(x2, y2, z2, 1.f);
            }
        }
        m_currentFormat = XYZ;
    }
}

void Image::xyz2rgb()
{
    if (m_currentFormat == XYZ)
    {
        Mat xyzImg(m_Height, m_Width, DataType<Vec3f>::type);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                Vec3f xyz = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                xyzImg.at<Vec3f>(y, x) = xyz; //Inversion of x and y, as opencv deals with image that way.
            }
        }
        Mat rgbImg;
        cvtColor(xyzImg, rgbImg, CV_XYZ2RGB);

        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                float r = rgbImg.at<Vec3f>(y, x)(0); //Inversion of x and y, as opencv deals with image that way.
                float g = rgbImg.at<Vec3f>(y, x)(1);
                float b = rgbImg.at<Vec3f>(y, x)(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(r, g, b, 1.f);
            }
        }
        m_currentFormat = RGB;
    }
}

void Image::color2gray()
{
    if (m_currentFormat == RGB)
    {
        for (unsigned int y = 0 ; y < m_Height ; ++y)
        {
            for (unsigned int x = 0 ; x < m_Width ; ++x)
            {
                Vec3f rgb = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                float l = 0.2126*rgb(0) + 0.7152*rgb(1) + 0.0722*rgb(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(l, l, l, 1.f);
            }
        }

        m_currentFormat = GRAY;
    }
    else if (m_currentFormat == HSV)
    {
        hsv2rgb();
        color2gray();
    }
    else if (m_currentFormat == XYZ)
    {
        xyz2rgb();
        color2gray();
    }
}

void Image::computeRGBMinMax()
{
    for (unsigned int y = 0 ; y < m_Height ; ++y)
    {
        for (unsigned int x = 0 ; x < m_Width ; ++x)
        {
            Eigen::Vector3f rgb = Eigen::Vector3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
            float l = 0.2126*rgb(0) + 0.7152*rgb(1) + 0.0722*rgb(2);

            m_MaxRGB = (l > m_MaxRGB)? l : m_MaxRGB;
            m_MinRGB = (l < m_MinRGB)? l : m_MinRGB;
        }
    }
}

void Image::computeMinMax()
{
    computeXYZMinMax();
    computeRGBMinMax();
}

void Image::computeXYZMinMax()
{
    rgb2xyz();
    for (unsigned int y = 0 ; y < m_Height ; ++y)
    {
        for (unsigned int x = 0 ; x < m_Width ; ++x)
        {
            Eigen::Vector3f pixel = Eigen::Vector3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
            m_MaxXYZ = (pixel(1) > m_MaxXYZ)? pixel(1) : m_MaxXYZ;
            m_MinXYZ = (pixel(1) < m_MinXYZ)? pixel(1) : m_MinXYZ;
        }
    }
    xyz2rgb();
}

void Image::normalizeRGB()
{
    for (unsigned int y = 0 ; y < m_Height ; ++y)
    {
        for (unsigned int x = 0 ; x < m_Width ; ++x)
        {
            for (unsigned int z = 0; z < 3; ++z)
            {
                m_Pixel[x + m_Width*y](z) = m_Pixel[x + m_Width*y](z)/m_MaxRGB;
            }
        }
    }
}

void Image::toneMapping()
{
    using namespace Eigen;
    float fp(-5.f), fparam, k, m, Lmean(0.f), c(0.5f), a(0.5f);

    fparam = exp(-fp);

    float max(0.f), min(1000.f);
    Vector3f channelAv(0.f, 0.f, 0.f);
    for (int y = 0; y < m_Height; ++y)
        for (int x = 0; x < m_Width; ++x)
        {
            float r = 255.f*m_Pixel[x + m_Width*y](0);
            float g = 255.f*m_Pixel[x + m_Width*y](1);
            float b = 255.f*m_Pixel[x + m_Width*y](2);

            float l = 0.2125*r + 0.7154*g + 0.0721*b;

            max = (l > max)? l : max;
            min = (l < min)? l : min;

            channelAv = channelAv + Vector3f(r/(m_Height*m_Width), g/(m_Height*m_Width), b/(m_Height*m_Width));
        }

    Lmean = 0.2125*channelAv(0) + 0.7154*channelAv(1) + 0.0721*channelAv(2);
    float logMean = log(Lmean);
    float logMax = log(max);
    float logMin = log((min < 0.01f) ? 0.01f : min);

    k = (logMax - logMean)/(logMax - logMin);
    m = 0.3f + 0.7f*pow(k, 1.4);

    for (int y = 0; y < m_Height; ++y)
        for (int x = 0; x < m_Width; ++x)
        {
            Vector3f color(255.f*m_Pixel[x + m_Width*y](0), 255.f*m_Pixel[x + m_Width*y](1), 255.f*m_Pixel[x + m_Width*y](2));

            float l = 0.2125*color(0) + 0.7154*color(1) + 0.0721*color(2);

            for (int k = 0; k < 3; ++k)
            {
                float ILocal = c*color(k) + (1.f - c)*l;
                float IGlobal = c*channelAv(k) + (1.f - c)*Lmean;
                float Ia = a*ILocal + (1.f - a)*IGlobal;
                color(k) /= color(k) + pow(fparam * Ia, m);
            }
            m_Pixel[x + m_Width*y] = Vector4f(color(0), color(1), color(2), 1.f);
        }
}
