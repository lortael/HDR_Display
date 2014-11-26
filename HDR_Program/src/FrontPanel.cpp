#include "FrontPanel.h"

#include <sstream>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

FrontPanel::FrontPanel()
//    : m_Height(0),
//      m_Width(0),
//      m_DisplayId(0),
//      m_GlWidget()
{

}

//FrontPanel::FrontPanel(unsigned int height, unsigned int width, Image const &img, unsigned int id)
//    : m_Height(height),
//      m_Width(width),
//      m_DisplayId(id),
//      m_GlWidget()
//{

//}

void FrontPanel::displayImageCV(Image &img) ////DEPRECATED : see displayImageGL()
{
    Mat imgMat;
    IMG_FORMAT initialFormat = img.format();
    if (img.format() != GRAY && img.format() == RGB)
    {
        Mat colorImg(img.height(), img.width(), DataType<Vec3f>::type);

        for (int y = 0 ; y < img.height() ; ++y)
        {
            for (int x = 0 ; x < img.width() ; ++x)
            {
                Vec3f rgb = Vec3f(img.pixel(x, y)(0), img.pixel(x, y)(1), img.pixel(x, y)(2));
                colorImg.at<Vec3f>(y, x) = rgb;
            }
        }
        Mat bgrImg;
        cvtColor(colorImg, bgrImg, CV_RGB2BGR);
        imgMat = bgrImg;

    }
    else if (img.format() != GRAY && img.format() == HSV)
    {
        img.hsv2rgb();
        displayImageCV(img);
        initialFormat = HSV;
    }

    if (initialFormat != HSV) //avoid displaying twice an HSV format image
    {
        std::stringstream ss;
        ss << m_DisplayId;
        std::string displayId = ss.str();

        std::string name = "Window " + displayId;

        cv::namedWindow(name, CV_WINDOW_NORMAL);
        cv::resizeWindow(name, img.width(), img.height());

        cv::imshow(name, imgMat);
    }
}

void FrontPanel::displayImageGL(Image &img)
{
    m_GlWidget.loadImage(img);
    m_GlWidget.resize(1920,1080);
    m_GlWidget.show();
}
