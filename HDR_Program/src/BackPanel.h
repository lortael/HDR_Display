#ifndef BACKPANEL_H_INCLUDED
#define BACKPANEL_H_INCLUDED

#include "DisplayDevice.h"
#include "HDRProcess.h"
#include "correction/Linearisation.h"

class BackPanel : public DisplayDevice, public HDRProcess
{
public :

    BackPanel();

//    BackPanel(unsigned int height, unsigned int width, unsigned int id);

    void displayImageCV(Image &img);

    void displayImageGL(Image &img);

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel);

    void computeShaderParameters();

    void computeShader();

private:

    Linearisation m_Linearisation;

protected:

};

#endif //BACKPANEL_H_INCLUDED
