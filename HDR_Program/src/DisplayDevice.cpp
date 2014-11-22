#include "DisplayDevice.h"

#include <sstream>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

DisplayDevice::DisplayDevice()
    : m_Image(),
      m_Height(0),
      m_Width(0),
      m_DisplayId(0)
{

}

DisplayDevice::DisplayDevice(unsigned int height, unsigned int width, Image const &img, unsigned int id)
    : m_Image(img),
      m_Height(height),
      m_Width(width),
      m_DisplayId(id)
{

}

DisplayDevice::~DisplayDevice()
{

}

void DisplayDevice::initDisplay()
{

}

void DisplayDevice::displayImageCV()
{
    Mat img;
    IMG_FORMAT initialFormat = m_Image.format();
    if (m_Image.format() != GRAY && m_Image.format() == RGB)
    {
        Mat colorImg(m_Image.height(), m_Image.width(), DataType<Vec3f>::type);

        for (int y = 0 ; y < m_Image.height() ; y++)
        {
            for (int x = 0 ; x < m_Image.width() ; x++)
            {
                Vec3f rgb = Vec3f(m_Image.pixel(x, y)(0), m_Image.pixel(x, y)(1), m_Image.pixel(x, y)(2));
                colorImg.at<Vec3f>(y, x) = rgb;
            }
        }
        Mat bgrImg;
        cvtColor(colorImg, bgrImg, CV_RGB2BGR);
        img = bgrImg;

    }
    else if (m_Image.format() != GRAY && m_Image.format() == HSV)
    {
        m_Image.hsv2rgb();
        displayImageCV();
        initialFormat = HSV;
    }
    else
    {
        Mat grayImg(m_Image.height(), m_Image.width(), DataType<float>::type);

        for (int y = 0 ; y < m_Image.height() ; y++)
        {
            for (int x = 0 ; x < m_Image.width() ; x++)
            {
                Vec3f rgb = Vec3f(m_Image.pixel(x, y)(0), m_Image.pixel(x, y)(1), m_Image.pixel(x, y)(2));
                grayImg.at<float>(y, x) = rgb(0);
            }
        }
        Mat bgrImg;
        cvtColor(grayImg, bgrImg, CV_GRAY2BGR);
        img = bgrImg;
    }

    if (initialFormat != HSV) //avoid displaying twice an HSV format image
    {
        std::stringstream ss;
        ss << m_DisplayId;
        std::string displayId = ss.str();

        std::string name = "Window " + displayId;

        cv::namedWindow(name, CV_WINDOW_NORMAL);
        cv::resizeWindow(name, m_Image.width(), m_Image.height());

        cv::imshow(name, img);
    }
}

void DisplayDevice::resize(unsigned int height, unsigned int width)
{
    m_Height = height;
    m_Width = width;
}
