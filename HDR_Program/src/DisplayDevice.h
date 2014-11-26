#ifndef DISPLAYDEVICE_H_INCLUDED
#define DISPLAYDEVICE_H_INCLUDED

#include "Image.h"
#include "HDRProcess.h"
#include "Correction.h"

#include "../glrendering/RenderingWidget.h"

class DisplayDevice
{
public :

    DisplayDevice();

    DisplayDevice(unsigned int height, unsigned int width, unsigned int id);

    virtual ~DisplayDevice();

    virtual void initDisplay();

    virtual unsigned int height() const {return m_Height;}
    virtual unsigned int width() const {return m_Width;}

    virtual void resize(unsigned int height, unsigned int width);

    virtual void setHeight(unsigned int height) {m_Height = height;}
    virtual void setWidth(unsigned int width) {m_Width = width;}

    virtual void displayImageCV(Image &img) = 0;

    virtual void displayImageGL(Image &img) = 0;

    virtual void setId(unsigned int id) {m_DisplayId = id;}
    virtual unsigned int id() {return m_DisplayId;}

    virtual void setName(QString name) {m_DisplayName = name;}

private:

protected:

    unsigned int m_Height;
    unsigned int m_Width;

    unsigned int m_DisplayId;
    QString m_DisplayName;

    RenderingWidget m_GlWidget;

    Correction m_Correction;
};

#endif //DISPLAYDEVICE_H_INCLUDED
