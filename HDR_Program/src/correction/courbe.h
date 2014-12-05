#ifndef COURBE_H
#define COURBE_H

#include <iostream>
#include <vector>
#include <string>

class Courbe
{
public:
    Courbe();
    Courbe(std::vector<float> coeffs);
    Courbe(std::string filename);

    float getValue(float x);
    void setCoeffs(std::vector<float> coeffs);
    void setCoeff(float coeff, int i);
    std::vector<float> getCoeffs();
    float dichotomie(float value);

    void operator=(Courbe courbe);

private:
    std::vector<float> _coeffs;
};

#endif // COURBE_H
