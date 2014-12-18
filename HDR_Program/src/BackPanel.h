/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Class to manage the back LCD panel, which will display a grayscale image to serve as backlighting.
 * */

#ifndef BACKPANEL_H_INCLUDED
#define BACKPANEL_H_INCLUDED

#include "DisplayDevice.h"
#include "HDRProcess.h"
#include "correction/Linearisation.h"

class BackPanel : public DisplayDevice, public HDRProcess
{
public :

    BackPanel();

    /**
     * @brief displays an image on target screen using openCV after applying the CPUprocess (no correction of response curve).
     * @param img, the Image to be displayed.
     * @see CPUprocess()
     * */    
    void displayImageCV(Image const &img);

    /**
     * @brief displays an image on target screen using openGL, by setting all the necessary attributes in the RenderingWidget.
     * @param img, the Image to be displayed.
     * @see RenderingWidget
     * */
    void displayImageGL(Image const &img);

private:

    Linearisation m_Linearisation;

protected:

    /**
     * @brief applies the square-root process on an image.
     * @param img, the Image to be displayed.
     * @return the processed image.
     * */
    Image CPUprocess(Image const &img);

};

#endif //BACKPANEL_H_INCLUDED
