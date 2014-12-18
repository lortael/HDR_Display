#include "FrontPanel.h"

#include <sstream>
#include <QDesktopWidget>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

FrontPanel::FrontPanel()
{

}

IMG_FORMAT initialFrontFormat;
void FrontPanel::displayImageCV(Image const &img) ////DEPRECATED : see displayImageGL()
{
    Image tempImg;
    tempImg = CPUprocess(img);

    //Converting Image to mat for use with OpenCV.
    Mat imgMat;
    initialFrontFormat = tempImg.format();
    if (tempImg.format() != GRAY && tempImg.format() == RGB)
    {
        Mat colorImg(tempImg.height(), tempImg.width(), DataType<Vec3f>::type);

        for (unsigned int y = 0 ; y < tempImg.height() ; ++y)
        {
            for (unsigned int x = 0 ; x < tempImg.width() ; ++x)
            {
                Vec3f rgb = Vec3f(tempImg.pixel(x, y)(0), tempImg.pixel(x, y)(1), tempImg.pixel(x, y)(2));
                colorImg.at<Vec3f>(y, x) = rgb;
            }
        }
        Mat bgrImg;
        cvtColor(colorImg, bgrImg, CV_RGB2BGR);
        imgMat = bgrImg;

    }
    else if (tempImg.format() != GRAY && tempImg.format() == HSV)
    {
        tempImg.hsv2rgb();
        displayImageCV(tempImg);
        initialFrontFormat = HSV;
    }

    if (initialFrontFormat != HSV) //Avoid displaying twice an HSV format image
    {
        std::string name = "Front panel";

        cv::namedWindow(name, CV_WINDOW_NORMAL);
        cv::resizeWindow(name, img.width(), img.height());

        cv::imshow(name, imgMat);
    }
}

void FrontPanel::displayImageGL(Image const &img)
{
    m_GlWidget->setWindowTitle("Front Panel");    

    Image cpyImg(img);
    m_GlWidget->loadImage(cpyImg);
    m_GlWidget->loadShaders(HDR_DIR"/shaders/frontPanel.vert", HDR_DIR"/shaders/frontPanel.frag");

    QDesktopWidget *backDesktop = QApplication::desktop();
    QRect screenGeo = backDesktop->availableGeometry(m_DisplayId);
    if (m_CurrentMode == FULLSCREEN)
        m_GlWidget->showFullScreen();
    else
    {
        m_GlWidget->resize(screenGeo.size());
        m_GlWidget->show();
    }
    //Move the window to the target device.
    m_GlWidget->move(screenGeo.topLeft());

    if (m_ToneMapped)
        m_GlWidget->toggleToneMapping();
    else
        m_GlWidget->toggleHDRDisplay();

    //Compute and set tone-mapping parameters.
    computeShaderParameters(cpyImg);
    m_GlWidget->setToneMappingParameters(m_Parameters);
}

Image FrontPanel::CPUprocess(const Image &img)
{
    Image temp(img);
    if (m_ToneMapped)
        temp.toneMapping();
    else
        for (unsigned int y = 0; y < img.height(); ++y)
            for (unsigned int x = 0; x < img.width(); ++x)
            {
                float r = img.pixel(x, y)(0);
                r = sqrt(r);
                float g = img.pixel(x, y)(1);
                g = sqrt(g);
                float b = img.pixel(x, y)(2);
                b = sqrt(b);
                temp.setPixel(x, y, Eigen::Vector4f(r, g, b, 1.f));
            }

    return temp;
}
