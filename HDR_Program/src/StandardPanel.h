/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Class to manage the main device to compare with the HDR process.
 * */

#ifndef STANDARDPANEL_H_INCLUDED
#define STANDARDPANEL_H_INCLUDED

#include "DisplayDevice.h"
#include "HDRProcess.h"
#include "correction/Linearisation.h"

class StandardPanel : public DisplayDevice, public HDRProcess
{
public :

    StandardPanel();

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
     * @brief apply tone-mapping from Image class.
     * @param img, the Image to be tone-mapped.
     * @return the tone-mapped image.
     * */
    Image CPUprocess(Image const &img);
};

#endif //STANDARDPANEL_H_INCLUDED
