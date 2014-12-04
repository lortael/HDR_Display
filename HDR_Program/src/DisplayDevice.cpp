#include "DisplayDevice.h"
#include "ImageIO.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

DisplayDevice::DisplayDevice()
    : m_Height(0),
      m_Width(0),
      m_DisplayId(0),
      m_GlWidget()
{

}

DisplayDevice::~DisplayDevice()
{

}

void DisplayDevice::initDisplay()
{

}

void DisplayDevice::resize(unsigned int height, unsigned int width)
{
    m_Height = height;
    m_Width = width;
}

void DisplayDevice::closeGlWindow()
{
    m_GlWidget.close();
}

void DisplayDevice::toggleFullscreen()
{
    m_GlWidget.changeScreenMode(FULLSCREEN);
}

void DisplayDevice::toggleWindow()
{
    m_GlWidget.changeScreenMode(WINDOW);
}
