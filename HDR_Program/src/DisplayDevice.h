#ifndef DISPLAYDEVICE_H_INCLUDED
#define DISPLAYDEVICE_H_INCLUDED

#include "Image.h"

#include "../glrendering/RenderingWidget.h"

class DisplayDevice
{
public :

    DisplayDevice();

    DisplayDevice(unsigned int height, unsigned int width, Image const &img, unsigned int id);

    ~DisplayDevice();

    void initDisplay();

    void importImage(Image const &img) {m_Image = img;}

    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}

    void resize(unsigned int height, unsigned int width);

    void setHeight(unsigned int height) {m_Height = height;}
    void setWidth(unsigned int width) {m_Width = width;}

    void displayImageCV();

    void displayImageGL();

    void setId(unsigned int id) {m_DisplayId = id;}
    unsigned int id() {return m_DisplayId;}


private:

protected:

    unsigned int m_Height;
    unsigned int m_Width;

    unsigned int m_DisplayId;

    Image m_Image;

    RenderingWidget m_Widget;

};

#endif //DISPLAYDEVICE_H_INCLUDED
