#include "Window.h"

Window::Window()
{

}

Window::Window(unsigned int height, unsigned int width, cv::Mat img, std::string name)
    : m_Height(height),
      m_Width(width),
      m_Image(img),
      m_WindowName(name)
{

}

Window& Window::operator=(Window const & win)
{
    m_Width = win.m_Width;
    m_Height = win.m_Height;
    m_WindowName = win.m_WindowName;

    m_Image = win.m_Image;

    return *this;
}
