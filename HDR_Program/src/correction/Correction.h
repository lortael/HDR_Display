#ifndef CORRECTION_H
#define CORRECTION_H

#include <Eigen/Core>

class Correction
{
public :
    Correction();

    virtual float evalPixel(float value) = 0;
    virtual Eigen::Vector4f processPixel(Eigen::Vector4f pixel, float maxVal) = 0;

private:

protected:

};

#endif CORRECTION_H
