#ifndef HDRPROCESS_H_INCLUDED
#define HDRPROCESS_H_INCLUDED

#include "Image.h"

class HDRProcess
{
public :

    Image CPUprocess(Image const &img);

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel);

    void GPUprocess(Image const &img);

    void computeShaderParameters();

    void computeShader();

private:

protected:

};

#endif //HDRPROCESS_H_INCLUDED
