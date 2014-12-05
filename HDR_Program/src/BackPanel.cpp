#include "BackPanel.h"

#include <sstream>
#include <QDesktopWidget>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

BackPanel::BackPanel()
{

}

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
    m_GlWidget.setWindowTitle("Back Panel");

    QDesktopWidget *backDesktop = QApplication::desktop();
    QRect screenGeo = backDesktop->availableGeometry();
    m_GlWidget.move(screenGeo.topLeft());

    img.color2gray();

    m_Linearisation.setCourbe(Courbe(std::string(HDR_DIR"/data/fitcurve_standard.cfg")));

    m_GlWidget.loadCurve(m_Linearisation.getLinTable());
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
    return pixel;
}

void BackPanel::computeShaderParameters()
{

}

void BackPanel::computeShader()
{

}
