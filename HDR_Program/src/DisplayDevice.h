/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
 * */

#ifndef DISPLAYDEVICE_H_INCLUDED
#define DISPLAYDEVICE_H_INCLUDED

#include "Image.h"
#include "HDRProcess.h"
#include "correction/Correction.h"

#include "../glrendering/RenderingWidget.h"

enum SCREENMODE {FULLSCREEN = 0, WINDOW = 1};

class DisplayDevice
{
public :

    DisplayDevice();

    virtual ~DisplayDevice();

    void initDevice();

    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}

    void resize(unsigned int height, unsigned int width);

    void setHeight(unsigned int height) {m_Height = height;}
    void setWidth(unsigned int width) {m_Width = width;}

    virtual void displayImageCV(Image &img) = 0;

    virtual void displayImageGL(Image const &img) = 0;

    virtual void updateImageGL(Image const &img) = 0;

    void setId(unsigned int id) {m_DisplayId = id;}
    unsigned int id() {return m_DisplayId;}

    void setName(QString name) {m_DisplayName = name;}

    void closeGlWindow();

    void toggleFullscreen() {m_CurrentMode = FULLSCREEN;}
    void toggleWindow() {m_CurrentMode = WINDOW;}

    RenderingWidget* glWidget() {return m_GlWidget;}

private:

protected:

    unsigned int m_Height;
    unsigned int m_Width;

    unsigned int m_DisplayId;
    QString m_DisplayName;

    SCREENMODE m_CurrentMode;

    RenderingWidget* m_GlWidget;
};

#endif //DISPLAYDEVICE_H_INCLUDED
