#include "DisplayDevice.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

DisplayDevice::DisplayDevice()
{

}

DisplayDevice::DisplayDevice(unsigned int height, unsigned int width, Image const &img, unsigned int id)
{

}

DisplayDevice::~DisplayDevice()
{

}

void DisplayDevice::initDisplay()
{

}

void DisplayDevice::displayImage()
{
    Mat img(m_Image.height(), m_Image.width(), DataType<Vec3f>::type);

    for (int y = 0 ; y < m_Image.height() ; y++)
    {
        for (int x = 0 ; x < m_Image.height() ; x++)
        {
            Vec3f rgb = Vec3f(m_Image.pixel(x, y)(0), m_Image.pixel(x, y)(1), m_Image.pixel(x, y)(2));
            img.at<Vec3f>(y, x) = rgb;
        }
    }

    //To display an image
    cv::namedWindow("win1", CV_WINDOW_NORMAL);
    cv::resizeWindow("win1", m_Image.width(), m_Image.height());
    Mat bgrImg;
    cvtColor(img, bgrImg, CV_RGB2BGR);
    cv::imshow("win1", bgrImg);
    waitKey(0);
}
