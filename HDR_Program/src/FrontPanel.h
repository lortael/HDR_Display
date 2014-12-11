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

    void displayImageCV(Image &img);

    void displayImageGL(Image const &img);

    void updateImageGL(Image const &img);

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel);

private:

protected:

    void computeShaderParameters(Image const &img);

};

#endif //FRONTPANEL_H_INCLUDED
