#include "StandardPanel.h"

#include <sstream>
#include <QDesktopWidget>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

StandardPanel::StandardPanel()
{

}

void StandardPanel::displayImageCV(Image &img) ////DEPRECATED : see displayImageGL()
{
    Image grayImg(img);
    Mat imgMat;
    if (grayImg.format() != GRAY)
        grayImg.color2gray();

    grayImg = CPUprocess(grayImg);

    Mat grayMatImg(grayImg.height(), grayImg.width(), DataType<Vec3f>::type);
    for (int y = 0 ; y < grayImg.height() ; ++y)
    {
        for (int x = 0 ; x < grayImg.width() ; ++x)
        {
            Vec3f grayscale = Vec3f(grayImg.pixel(x, y)(0), grayImg.pixel(x, y)(1), grayImg.pixel(x, y)(2));
            grayMatImg.at<Vec3f>(y, x) = grayscale;
        }
    }
    Mat bgrImg;
    cvtColor(grayMatImg, bgrImg, CV_RGB2BGR);
    imgMat = bgrImg;

    std::stringstream ss;
    ss << m_DisplayId;
    std::string displayId = ss.str();

    std::string name = "Window " + displayId;

    cv::namedWindow(name, CV_WINDOW_NORMAL);
    cv::resizeWindow(name, img.width(), img.height());

    cv::imshow(name, imgMat);
}

void StandardPanel::displayImageGL(Image const &img)
{
    Image cpyImg(img);
    cpyImg.setFormat(GRAY);
    m_GlWidget->setWindowTitle("Main Panel");

    QDesktopWidget *backDesktop = QApplication::desktop();
    QRect screenGeo = backDesktop->availableGeometry(m_DisplayId);

    m_GlWidget->loadImage(cpyImg);
    m_GlWidget->loadShaders(HDR_DIR"/shaders/standardPanel.vert", HDR_DIR"/shaders/standardPanel.frag");
    if (m_CurrentMode == FULLSCREEN)
        m_GlWidget->showFullScreen();
    else
    {
        m_GlWidget->resize(1920,1080);
        m_GlWidget->show();
    }
    m_GlWidget->move(screenGeo.topLeft());
}

void StandardPanel::updateImageGL(Image const &img)
{
    m_GlWidget->loadImage(img);
    m_GlWidget->updateTexture();
}

Eigen::Vector4f StandardPanel::processPixel(Eigen::Vector4f pixel)
{
    float r = pixel(0);
    float g = pixel(1);
    float b = pixel(2);

    Eigen::Vector4f outPixel(sqrt(r), sqrt(g), sqrt(b), 1.f);
    return outPixel;
}

void StandardPanel::computeShaderParameters(Image const &img)
{

}

Image StandardPanel::computePSFImage(Image const &img, unsigned int psfSize)
{
//    Image temp(img);



//    for (int y = 0 ; y < temp.height() ; ++y)
//    {
//        for (int x = 0 ; x < temp.width() ; ++x)
//        {

//        }
//    }
}

float StandardPanel::convolutionKernel(unsigned int x, unsigned int y, Image const &img, unsigned int psfSize)
{
//    unsigned int topY;
//    topY = (y > img.height() - psfSize) ? img.height() - y : psfSize;
//    unsigned int botY;
//    botY = (y < psfSize) ? psfSize - y : psfSize;
//    unsigned int leftX;
//    leftX = (x < psfSize) ? psfSize - x : psfSize;
//    unsigned int rightX;
//    rightX = (x > img.width() - psfSize) ? img.width() - x : psfSize;

//    float sum(0);
//    int coeff(1);
//    Eigen::Matrix<unsigned int, psfSize, psfSize> coeffs;
//    for (unsigned int i = - botY; i < topY; ++i)
//        for (unsigned int j = -leftX; j < rightX; ++j)
//        {
//            sum += coeff
//        }

//    return value;
}
