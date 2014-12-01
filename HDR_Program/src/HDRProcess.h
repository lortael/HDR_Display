#ifndef HDRPROCESS_H_INCLUDED
#define HDRPROCESS_H_INCLUDED

#include "Image.h"

class HDRProcess
{
public :

    Image CPUprocess(Image const &img);

    virtual Eigen::Vector4f processPixel(Eigen::Vector4f pixel) = 0;

    virtual void GPUprocess(Image const &img);

    virtual void computeShaderParameters() = 0;

    virtual void computeShader() = 0;

private:

protected:

};

#endif //HDRPROCESS_H_INCLUDED
