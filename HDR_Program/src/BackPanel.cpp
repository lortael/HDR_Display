#include "BackPanel.h"

#include <sstream>
#include <QDesktopWidget>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

BackPanel::BackPanel()
    : m_Linearisation()
{

}

void BackPanel::displayImageCV(Image const &img) ////DEPRECATED : see displayImageGL()
{
    Image grayImg(img);    
    if (grayImg.format() != GRAY)
        grayImg.color2gray();

    grayImg = CPUprocess(grayImg);

    //Converting Image to mat for use with OpenCV.
    Mat imgMat;
    Mat grayMatImg(grayImg.height(), grayImg.width(), DataType<Vec3f>::type);
    for (int y = 0 ; y < grayImg.height() ; ++y)
    {
        for (int x = 0 ; x < grayImg.width() ; ++x)
        {
            float grayscale = grayImg.pixel(x, y)(0);
            grayMatImg.at<Vec3f>(y, x) = Vec3f(grayscale, grayscale, grayscale);
        }
    }
    Mat bgrImg;
    cvtColor(grayMatImg, bgrImg, CV_RGB2BGR);
    imgMat = bgrImg;

    std::string name = "Back panel";

    cv::namedWindow(name, CV_WINDOW_NORMAL);
    cv::resizeWindow(name, img.width(), img.height());

    cv::imshow(name, imgMat);
}

void BackPanel::displayImageGL(Image const &img)
{
    Image cpyImg(img);
    cpyImg.setFormat(GRAY);
    m_GlWidget->setWindowTitle("Back Panel");

    QDesktopWidget *backDesktop = QApplication::desktop();
    QRect screenGeo = backDesktop->availableGeometry(m_DisplayId);

    m_Linearisation.loadCoeffFromFile(HDR_DIR"/data/fitcurve_standard.cfg");
    m_Linearisation.computeCurve();

    m_GlWidget->isBackPanel();
    m_GlWidget->loadCurve(m_Linearisation);
    m_GlWidget->loadImage(cpyImg);
    m_GlWidget->loadShaders(HDR_DIR"/shaders/backPanel.vert", HDR_DIR"/shaders/backPanel.frag");

    computeShaderParameters(cpyImg);
    m_GlWidget->setToneMappingParameters(m_Parameters);

    if (m_CurrentMode == FULLSCREEN)
        m_GlWidget->showFullScreen();
    else
    {
        m_GlWidget->resize(1920,1080);
        m_GlWidget->show();
    }
    m_GlWidget->move(screenGeo.topLeft());

    if (m_ToneMapped)
        m_GlWidget->toggleToneMapping();
    else
        m_GlWidget->toggleHDRDisplay();
}

Image BackPanel::CPUprocess(Image const &img)
{
    Image temp(img);

    if (m_ToneMapped)
        for (int y = 0; y < img.height(); ++y)
            for (int x = 0; x < img.width(); ++x)
            {
                temp.setPixel(x, y, Eigen::Vector4f(0.f, 0.f, 0.f, 1.f));
            }
    else
    {
        temp.normalizeRGB();
        for (int y = 0; y < img.height(); ++y)
            for (int x = 0; x < img.width(); ++x)
            {
                float r = img.pixel(x, y)(0);
                r = sqrt(r);
                temp.setPixel(x, y, Eigen::Vector4f(1.f-r, 1.f-r, 1.f-r, 1.f));
            }
    }

    return temp;
}
