#include "DisplayDevice.h"
#include "ImageIO.h"

DisplayDevice::DisplayDevice()
    : m_Height(0),
      m_Width(0),
      m_DisplayId(0),
      m_GlWidget()
{

}

DisplayDevice::DisplayDevice(unsigned int height, unsigned int width, unsigned int id)
    : m_Height(height),
      m_Width(width),
      m_DisplayId(id),
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
