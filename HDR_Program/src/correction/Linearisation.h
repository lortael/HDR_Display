#ifndef LINEARISATION_H
#define LINEARISATION_H

#include "Correction.h"
#include "courbe.h"
#include <vector>
#include <Eigen/Core>

class Linearisation
{
public:
    Linearisation();

    float getCoeff(unsigned int index) const {return m_Curve[index];}

    void loadCoeffFromFile(std::string filename);

    void computeCurve();


private:
    std::vector<float> m_coeffs;
    std::vector<float> m_Curve;

    float getValue (float x);

    float dichotomie(float value);

};

#endif // LINEARISATION_H
