#ifndef LINEARISATION_H
#define LINEARISATION_H

#include "Correction.h"
#include "courbe.h"
#include <vector>
#include <Eigen/Core>

class Linearisation : public Correction
{
public:
    Linearisation();
    Linearisation(Courbe courbe);
    void setCourbe(Courbe courbe);
    Courbe getCourbe();

    Eigen::Vector4f processPixel(Eigen::Vector4f pixel, float maxVal);
    float evalPixel(float value);

    float* getLinTable();

private:
    Courbe _courbe;
};

#endif // LINEARISATION_H
