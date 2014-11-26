#include "HDRProcess.h"




Image HDRProcess::CPUprocess(const Image &img)
{
    Image temp(img);
    for (int y = 0 ; y < temp.height() ; ++y)
    {
        for (int x = 0 ; x < temp.width() ; ++x)
        {
            temp.setPixel(x, y, processPixel(temp.pixel(x, y)));
        }
    }

    return temp;
}

void HDRProcess::GPUprocess(const Image &img)
{

}

Eigen::Vector4f HDRProcess::processPixel(Eigen::Vector4f pixel)
{

}
