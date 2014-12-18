#ifndef LINEARISATION_H
#define LINEARISATION_H

#include "Image.h"
#include <vector>
#include <Eigen/Core>

class Linearisation
{
public:
    Linearisation();

    float getCoeff(unsigned int index) const {return m_Curve[index];}

    /**
     * @brief loads the coefficients of the parametric response curve.
     * @param filename, the filename of the curve.
     * */
    void loadCoeffFromFile(std::string filename);

    /**
     * @brief computes the response curve array from the parametric coefficients.
     * */
    void computeCurve();

    /**
     * @brief converts an array to an image.
     * */
    Image &toImg();

private:
    std::vector<float> m_coeffs;
    std::vector<float> m_Curve;

    /** Function getValue (12/11/2014, Vincent Marie)
     *
     * arg in : x (float value 0<=x<=255 at which the poly should be evaled
     * arg out : sum (float value : curve evaluated at x point
     *
     * Evaluates the curve at a given point. The value of this point should
     * be between 0 and 255 (non-normalized value). The returned value is a
     * normalized value (between 0 and 1). */
    float getValue (float x);

    /** Function dichotomie (2014, David Murray)
     *
     * arg in : value (float for which the dichotomic search should be done)
     * arg out : float value (containing the result of dichotomic search
     *
     * Dichotomic search for a value on a given curve. */
    float dichotomie(float value);

};

#endif // LINEARISATION_H
