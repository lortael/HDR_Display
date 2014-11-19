#ifndef DISPLAYDEVICE_H_INCLUDED
#define DISPLAYDEVICE_H_INCLUDED

#include "Image.h"

class DisplayDevice
{
public :

    DisplayDevice();

    DisplayDevice(unsigned int height, unsigned int width, Image const &img, unsigned int id);

    ~DisplayDevice();

    void initDisplay();

    void importImage(Image const &img){m_Image = img;}

    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}
    void setHeight(int height) {m_Height = height;}
    void setWidth(int width) {m_Width = width;}

    void displayImage();


private:

protected:

    unsigned int m_Height;
    unsigned int m_Width;

    unsigned int m_DisplayId;

    Image m_Image;

};

#endif //DISPLAYDEVICE_H_INCLUDED
