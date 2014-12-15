/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
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

    void displayImageCV(Image const &img);

    void displayImageGL(Image const &img);

private:

    Linearisation m_Linearisation;

protected:

    Image CPUprocess(Image const &img);

    Image computePSFImage(Image const &img, unsigned int psfSize);

    float convolutionKernel(unsigned int x, unsigned int y, Image const &img, unsigned int psfSize);
};

#endif //BACKPANEL_H_INCLUDED
