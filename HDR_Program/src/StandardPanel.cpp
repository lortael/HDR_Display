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

IMG_FORMAT initialStandardFormat;
void StandardPanel::displayImageCV(Image const &img) ////DEPRECATED : see displayImageGL()
{
    Image tempImg;
    tempImg = CPUprocess(img);

    //Converting Image to mat for use with OpenCV.
    Mat imgMat;
    initialStandardFormat = tempImg.format();
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
        initialStandardFormat = HSV;
    }

    if (initialStandardFormat != HSV) //avoid displaying twice an HSV format image
    {
        std::string name = "Standard panel";

        cv::namedWindow(name, CV_WINDOW_NORMAL);
        cv::resizeWindow(name, img.width(), img.height());

        cv::imshow(name, imgMat);
    }
}

void StandardPanel::displayImageGL(Image const &img)
{
    Image cpyImg(img);
    m_GlWidget->setWindowTitle("Main Panel");

    m_GlWidget->loadImage(cpyImg);
    m_GlWidget->loadShaders(HDR_DIR"/shaders/standardPanel.vert", HDR_DIR"/shaders/standardPanel.frag");
    computeShaderParameters(img);
    m_GlWidget->setToneMappingParameters(m_Parameters);

    QDesktopWidget *backDesktop = QApplication::desktop();
    QRect screenGeo = backDesktop->availableGeometry(m_DisplayId);

    if (m_CurrentMode == FULLSCREEN)
        m_GlWidget->showFullScreen();
    else
    {
        m_GlWidget->resize(screenGeo.size());
        m_GlWidget->show();
    }

    m_GlWidget->move(screenGeo.topLeft());

    if (m_ToneMapped)
        m_GlWidget->toggleToneMapping();
    else
        m_GlWidget->toggleHDRDisplay();
}

Image StandardPanel::CPUprocess(const Image &img)
{
    Image temp(img);
    temp.toneMapping();
    return temp;
}

