#include "Image.h"


Image::Image()
{

}

Image::~Image()
{

}

Image::Image(Image& img)
{

}

Image& Image::operator=(Image const & img)
{
    m_Width = img.m_Width;
    m_Height = img.m_Height;
    m_Min = img.m_Min;
    m_Max = img.m_Max;

    m_Img = img.m_Img;

    return *this;
}
