#include "BackPanel.h"

#include <sstream>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

BackPanel::BackPanel()
//    : m_Height(0),
//      m_Width(0),
//      m_DisplayId(0),
//      m_GlWidget()
{

}

//BackPanel::BackPanel(unsigned int height, unsigned int width, Image const &img, unsigned int id)
//    : m_Height(height),
//      m_Width(width),
//      m_DisplayId(id),
//      m_GlWidget()
//{

//}

void BackPanel::displayImageCV(Image &img) ////DEPRECATED : see displayImageGL()
{
    Mat imgMat;
    if (img.format() != GRAY)
        img.color2gray();

    std::stringstream ss;
    ss << m_DisplayId;
    std::string displayId = ss.str();

    std::string name = "Window " + displayId;

    cv::namedWindow(name, CV_WINDOW_NORMAL);
    cv::resizeWindow(name, img.width(), img.height());

    cv::imshow(name, imgMat);
}

void BackPanel::displayImageGL(Image &img)
{
    img.color2gray();
    m_GlWidget.loadImage(img);
    m_GlWidget.resize(1920,1080);
    m_GlWidget.show();
}
