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

    virtual ~DisplayDevice();

    void initDisplay();

    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}

    void resize(unsigned int height, unsigned int width);

    void setHeight(unsigned int height) {m_Height = height;}
    void setWidth(unsigned int width) {m_Width = width;}

    virtual void displayImageCV(Image &img) = 0;

    virtual void displayImageGL(Image &img) = 0;

    void setId(unsigned int id) {m_DisplayId = id;}
    unsigned int id() {return m_DisplayId;}

    void setName(QString name) {m_DisplayName = name;}

    void closeGlWindow();

    void toggleFullscreen();
    void toggleWindow();

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
