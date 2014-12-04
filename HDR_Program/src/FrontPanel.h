#ifndef FRONTPANEL_H_INCLUDED
#define FRONTPANEL_H_INCLUDED

#include "DisplayDevice.h"

class FrontPanel : public DisplayDevice, public HDRProcess
{
public :

    FrontPanel();

    void displayImageCV(Image &img);

    void displayImageGL(Image &img);

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel);

//    void computeShaderParameters();

//    void computeShader();

private:

protected:

};

#endif //FRONTPANEL_H_INCLUDED
