/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Class to manage the front LCD panel, which will display a sharpened image to serve as backlighting.
 * */

#ifndef FRONTPANEL_H_INCLUDED
#define FRONTPANEL_H_INCLUDED

#include "DisplayDevice.h"

class FrontPanel : public DisplayDevice, public HDRProcess
{
public :

    FrontPanel();

    /**
     * @brief displays an image on target screen using openCV after applying the CPUprocess.
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

protected:

    /**
     * @brief applies the square-root process on an image.
     * @param img, the Image to be displayed.
     * @return the processed image.
     * */
    Image CPUprocess(Image const &img);

};

#endif //FRONTPANEL_H_INCLUDED
