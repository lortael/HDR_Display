/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
 * */

#ifndef FRONTPANEL_H_INCLUDED
#define FRONTPANEL_H_INCLUDED

#include "DisplayDevice.h"

class FrontPanel : public DisplayDevice, public HDRProcess
{
public :

    FrontPanel();

    void displayImageCV(Image const &img);

    void displayImageGL(Image const &img);

private:

protected:

    Image CPUprocess(Image const &img);

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel);

};

#endif //FRONTPANEL_H_INCLUDED
