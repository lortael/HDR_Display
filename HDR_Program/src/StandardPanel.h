/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
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

    void displayImageCV(Image const &img);

    void displayImageGL(Image const &img);

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel);

private:

protected:

};

#endif //STANDARDPANEL_H_INCLUDED
