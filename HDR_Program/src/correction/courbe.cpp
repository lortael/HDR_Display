#include "courbe.h"

#include <math.h>
#include <iostream>
#include <fstream>

Courbe::Courbe()
{
}

Courbe::Courbe(std::vector<float> coeffs)
{
    _coeffs = coeffs;
}

Courbe::Courbe(std::string filename)
{
    /** Curve constructor from file (01/12/2014, Vincent Marie)
     *
     * arg in : filename (std::string containing name of
     *                    config file)
     *
     * Loads curve from cfg file containing the coeffs of the polynomial
     * curve. Coeffs are loaded from degree 0 to MAX_DEGREE */

    /* Step 1 : Checking if filetype is .cfg */
    std::string filenameend;
    for(int i=4;i>0;i--)
    {
        filenameend.push_back(filename[filename.length()-i]);
    }

    if(filenameend == ".cfg")
    {
        /* If filetype is cfg, trying to open file */
        std::ifstream file(filename.c_str());

        if(file.is_open())
        {
            while(!file.eof())
            {
                float coeff;
                file >> coeff;
                _coeffs.push_back(coeff);
            }
            _coeffs.pop_back(); //Last element of file was read twice, so one pop_back is necessary
        }
        else
        {
            std::cout << "Error : file not loaded" << std::endl;
        }
    }
    else
    {
        std::cout << "Error : curve file must be .cfg" << std::endl;
    }
}

float Courbe::getValue(float x)
{
    /** Function getValue (12/11/2014, Vincent Marie)
     *
     * arg in : x (float value 0<=x<=255 at which the poly should be evaled
     * arg out : sum (float value : curve evaluated at x point
     *
     * Evaluates the curve at a given point. The value of this point should
     * be between 0 and 255 (non-normalized value). The returned value is a
     * normalized value (between 0 and 1). */

    float sum = 0;

    // Cas où coefficients non renseignés
    if(_coeffs.size() == 0)
    {
        std::cout << "Erreur : Pas de coefficients spécifiés" << std::endl;
    }
    else
    {
        for(int i=0; i<_coeffs.size(); i++)
        {
            sum += _coeffs[i]*pow(x,i);
        }
    }

    return(sum);
}

void Courbe::setCoeffs(std::vector<float> coeffs)
{
    /** Function setCoeffs (12/11/2014, Vincent Marie)
     *
     * arg in : coeffs (std::vector<float> containing polynomial coeffs)
     * arg out : none
     *
     * Fills the curve coefficients with an std::vector<float> containing
     * given coefficients. */

    _coeffs = coeffs;
}

void Courbe::setCoeff(float coeff, int i)
{
    /** Function setCoeff (12/11/2014, Vincent Marie)
     *
     * arg in : coeff (float containing the coeff to insert)
     *          i (int that is the corresponding degree to the coeff)
     * arg out : none
     *
     * Inserts the polynomial coefficient "coeff" at the curve coefficient
     * corresponding to the degree "i". */

    if(i>=_coeffs.size())
    {
        _coeffs.resize(i+1);
    }

    _coeffs[i] = coeff;
}

std::vector<float> Courbe::getCoeffs()
{
    /** Function getCoeffs (12/11/2014, Vincent Marie)
     *
     * arg in : none
     * arg out : _coeffs (std::vector<float> containing polynomial coeffs of the curve)
     *
     * Returns an std::vector<float> containing the polynomial coefficients of the curve
     * that is at stake. */

    return(_coeffs);
}

float Courbe::dichotomie(float value)
{
    /** Function dichotomie (2014, David Murray)
     *
     * arg in : value (float for which the dichotomic search should be done)
     * arg out : float value (containing the result of dichotomic search
     *
     * Dichotomic search for a value on a given curve. */

    if(value < 0. || value > 1.)
    {
        std::cout << "Erreur : la valeur doit etre comprise entre 0 et 1." << std::endl;
        return(0.);
    }
    else
    {
        float mil;
        float db = 0.;
        float fin = 255.;

        while (fin - db > 1.)
        {
            mil = (fin + db)/2.;

            if (value < getValue(mil))
            {
                fin = mil;
            }
            else
            {
                db = mil;
            }
        }

        return(1.0*(fin + db)/(2.*255.));
    }
}

void Courbe::operator=(Courbe courbe)
{
    /** Operator = (12/11/2014, Vincent Marie) */

    _coeffs.clear();
    _coeffs = courbe.getCoeffs();
}
