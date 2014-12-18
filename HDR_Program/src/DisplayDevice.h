/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Class representing a display device (monitor, projector...).
 * As such, it contains an Id associated with the hardware Id of the device.
 * Rendering for functions to display images are implemented in this class.
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

    /**
     * @brief : initializes the device by initializing the RenderingWidget.
     * */
    void initDevice();

    /**
     * @brief : displays an image on target screen using openCV (more details in inherited classes).
     * @param : the Image to be displayed
     * */
    /// /!\ Deprecated, should be used only if no GPU are available, or OpenGL version is below 3.0.
    /// @see displayImageGL()
    virtual void displayImageCV(Image const &img) = 0;

    /**
     * @brief : displays an image on target screen using OpenGL (more details in inherited classes).
     * @param : the Image to be displayed
     * */
    virtual void displayImageGL(Image const &img) = 0;

    /**
     * @brief : changes the displayed image in the OpenGL renderer.
     * @param : the new Image to be displayed
     * */
    void updateImageGL(Image const &img);

    /**
     * @brief : close the current OpenGL window and context.
     * */
    void closeGlWindow();

    void setId(unsigned int id) {m_DisplayId = id;}
    unsigned int id() {return m_DisplayId;}

    void setName(QString name) {m_DisplayName = name;}

    void toggleFullscreen() {m_CurrentMode = FULLSCREEN;}
    void toggleWindow() {m_CurrentMode = WINDOW;}

    RenderingWidget* glWidget() {return m_GlWidget;}

    void changeTM(bool tm) {m_ToneMapped = tm;}

private:

protected:

    bool m_ToneMapped;

    unsigned int m_DisplayId;
    QString m_DisplayName;

    SCREENMODE m_CurrentMode;

    RenderingWidget* m_GlWidget;
};

#endif //DISPLAYDEVICE_H_INCLUDED
