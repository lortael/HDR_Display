#include "DisplayDevice.h"
#include "ImageIO.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

DisplayDevice::DisplayDevice()
    : m_DisplayId(0),
      m_ToneMapped(false),
      m_GlWidget(NULL),
      m_CurrentMode(WINDOW)
{

}

DisplayDevice::~DisplayDevice()
{
    if (m_GlWidget != NULL)
        delete m_GlWidget;
}

void DisplayDevice::initDevice()
{
    m_GlWidget = new RenderingWidget();
}

void DisplayDevice::closeGlWindow()
{
    if (m_GlWidget->isActiveWindow())
        m_GlWidget->close();
    delete m_GlWidget;
}

void DisplayDevice::updateImageGL(Image const &img)
{
    m_GlWidget->loadImage(img);
    m_GlWidget->updateTextures();
}
