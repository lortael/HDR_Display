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
     * @brief : displays an image on target screen using openCV (more details in inherited classes).
     * @param : the Image to be displayed
     * */
    void displayImageCV(Image const &img);

    /**
     * @brief : displays an image on target screen using openCV (more details in inherited classes).
     * @param : the Image to be displayed
     * */
    void displayImageGL(Image const &img);

private:

    Linearisation m_Linearisation;

protected:

    Image CPUprocess(Image const &img);

};

#endif //BACKPANEL_H_INCLUDED
