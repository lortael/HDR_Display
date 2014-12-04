#include "BackPanel.h"

#include <sstream>
#include <QDesktopWidget>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

BackPanel::BackPanel()
{
    m_DisplayId = QApplication::desktop()->primaryScreen() + 1;
}

void BackPanel::displayImageCV(Image &img) ////DEPRECATED : see displayImageGL()
{
    Mat imgMat;
    if (img.format() != GRAY)
        img.color2gray();

    Mat grayImg(img.height(), img.width(), DataType<Vec3f>::type);
    for (int y = 0 ; y < img.height() ; ++y)
    {
        for (int x = 0 ; x < img.width() ; ++x)
        {
            Vec3f grayscale = Vec3f(img.pixel(x, y)(0), img.pixel(x, y)(1), img.pixel(x, y)(2));
            grayImg.at<Vec3f>(y, x) = grayscale;
        }
    }
    Mat bgrImg;
    cvtColor(grayImg, bgrImg, CV_RGB2BGR);
    imgMat = bgrImg;

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
    m_GlWidget.setWindowTitle("Back Panel");

    QDesktopWidget *backDesktop = QApplication::desktop();
    QRect screenGeo = backDesktop->availableGeometry(m_DisplayId);

    m_GlWidget.move(screenGeo.topLeft());

    img.color2gray();
    m_GlWidget.loadImage(img);
    if (m_GlWidget.screenmode() == FULLSCREEN)
        m_GlWidget.showFullScreen();
    else
    {
        m_GlWidget.resize(1920,1080);
        m_GlWidget.show();
    }
}

Eigen::Vector4f BackPanel::processPixel(Eigen::Vector4f pixel)
{
//    return Eigen::Vector4f(sqrt(pixel(0)), sqrt(pixel(1)), sqrt(pixel(2)), pixel(3));
    return pixel;
}

//void BackPanel::computeShaderParameters()
//{

//}

//void BackPanel::computeShader()
//{

//}
