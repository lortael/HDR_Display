#include "Image.h"


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
      m_Max(0.f, 0.f, 0.f),
      m_Min(50.f, 50.f ,50.f)
{
}

Image::Image(Image const &img)
{
    m_Width = img.m_Width;
    m_Height = img.m_Height;
    m_Min = img.m_Min;
    m_Max = img.m_Max;
    m_currentFormat = img.m_currentFormat;
    imageIsNULL = img.imageIsNULL;

//    initImage();

    m_Pixel = img.m_Pixel;

    cout << "init" << endl;
}

Image::~Image()
{

}

Image& Image::operator=(Image const & img)
{
    m_Width = img.m_Width;
    m_Height = img.m_Height;
    m_Min = img.m_Min;
    m_Max = img.m_Max;
    m_currentFormat = img.m_currentFormat;
    imageIsNULL = img.imageIsNULL;

//    initImage();

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

        for (int y = 0 ; y < m_Height ; y++)
        {
            for (int x = 0 ; x < m_Width ; x++)
            {
                Vec3f rgb = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                rgbImg.at<Vec3f>(y, x) = rgb; //Inversion of x and y, as opencv deals with image this way.
            }
        }

        Mat hsvImg(m_Height, m_Width, DataType<Vec3f>::type), nrgbImg(m_Height, m_Width, DataType<Vec3f>::type);
        cvtColor(rgbImg, hsvImg, CV_RGB2HSV);



        for (int y = 0; y < m_Height; y++)
        {
            for (int x = 0; x < m_Width; x++)
            {
                float h = hsvImg.at<Vec3f>(y, x)(0);
                float s = hsvImg.at<Vec3f>(y, x)(1);
                float v = hsvImg.at<Vec3f>(y, x)(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(h, s, v, 1.f);
            }
        }
        waitKey(0);
        m_currentFormat = HSV;
    }
}

void Image::hsv2rgb()
{
    if (m_currentFormat == HSV)
    {
        Mat hsvImg(m_Height, m_Width, DataType<Vec3f>::type);

        for (int y = 0 ; y < m_Height ; y++)
        {
            for (int x = 0 ; x < m_Width ; x++)
            {
                Vec3f hsv = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                hsvImg.at<Vec3f>(y, x) = hsv;
            }
        }
        Mat rgbImg;
        cvtColor(hsvImg, rgbImg, CV_HSV2RGB);

        for (int y = 0; y < m_Height; y++)
        {
            for (int x = 0; x < m_Width; x++)
            {
                float r = rgbImg.at<Vec3f>(y, x)(0);
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
        Mat rgbImg(m_Height, m_Width, DataType<Vec3f>::type);

        for (int y = 0 ; y < m_Height ; y++)
        {
            for (int x = 0 ; x < m_Width ; x++)
            {
                Vec3f rgb = Vec3f(m_Pixel[x + m_Width*y](0), m_Pixel[x + m_Width*y](1), m_Pixel[x + m_Width*y](2));
                rgbImg.at<Vec3f>(y, x) = rgb;
            }
        }
        Mat grayImg;
        cvtColor(rgbImg, grayImg, CV_RGB2GRAY);

        for (int y = 0; y < m_Height; y++)
        {
            for (int x = 0; x < m_Width; x++)
            {
                float r = rgbImg.at<Vec3f>(y, x)(0);
                float g = rgbImg.at<Vec3f>(y, x)(1);
                float b = rgbImg.at<Vec3f>(y, x)(2);
                m_Pixel[x + m_Width*y] = Eigen::Vector4f(r, g, b, 1.f);
            }
        }
        m_currentFormat = GRAY;
    }
    else if (m_currentFormat == HSV)
    {
        hsv2rgb();
        color2gray();
    }
}
