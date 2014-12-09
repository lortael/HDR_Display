#include "Linearisation.h"

#include <iostream>
#include <fstream>

Linearisation::Linearisation()
{

}

void Linearisation::loadCoeffFromFile(std::string filename)
{
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
                m_coeffs.push_back(coeff);
            }
            m_coeffs.pop_back(); //Last element of file was read twice, so one pop_back is necessary
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

void Linearisation::computeCurve()
{
    for(int i=0; i<256; i++)
    {
        float value = float(i)/255.f;
        m_Curve.push_back(dichotomie(value));
    }
}

float Linearisation::getValue(float x)
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
    if(m_coeffs.size() == 0)
    {
        std::cout << "Erreur : Pas de coefficients spécifiés" << std::endl;
    }
    else
    {
        for(int i=0; i< m_coeffs.size(); i++)
        {
            sum += m_coeffs[i]*pow(x,i);
        }
    }

    return(sum);
}

float Linearisation::dichotomie(float value)
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
