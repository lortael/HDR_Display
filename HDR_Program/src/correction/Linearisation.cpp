#include "Linearisation.h"

#include <iostream>
#include <fstream>

Linearisation::Linearisation()
{
}

Linearisation::Linearisation(Courbe courbe)
{
    _courbe = courbe;
}

void Linearisation::setCourbe(Courbe courbe)
{
    _courbe = courbe;
}

float Linearisation::evalPixel(float value)
{
    /** Function processPixel (01/12/2014, Vincent Marie)
     *
     * arg in : value (float value to be linearized)
     * arg out : valObtained (float value linearized)
     *
     * Computing a linearized value from an input value */

    /* Old : generating sampled linearized values for calibration
    std::ofstream txtfile;
    txtfile.open("lin.txt");
    for(int i=0; i<21; i++)
    {
        float valW = i*5./100.;
        txtfile << _courbe.dichotomie(valW) << std::endl;
    }
    txtfile.close();*/

    float valObtained = _courbe.dichotomie(value);

    /*std::cout << "Valeur souhaitée : " << value << std::endl;
    std::cout << "Valeur obtenue : " << valObtained << std::endl;
    std::cout << "Affichage : " << _courbe.getValue(valObtained*255.) << std::endl;*/

    return valObtained;
}

Eigen::Vector4f Linearisation::processPixel(Eigen::Vector4f pixel, float maxVal)
{
    /** Function processPixel (02/12/2014, Vincent Marie)
     *
     * arg in : pixel (Vector4f&, pixel to be processed)
     * arg out : none
     *
     * Processes the linearization on a given pixel */
    Eigen::Vector4f procPix(0.,0.,0.,1.f);

    procPix[0] = evalPixel(pixel[0]/maxVal)*maxVal;
    procPix[1] = procPix[0];
    procPix[2] = procPix[0];

    return procPix;
}

float* Linearisation::getLinTable()
{
    /** Function genLinTable (02/12/2014, Vincent Marie)
     *
     * arg in : none
     * arg out : LinTable (std::vector<float> containing 256 linearized values)
     *
     * Generates a table of 256 float values
     * The table contains linearized value for each pixel value */

    float* LinTable;
    LinTable = new float[256];

    for(int i=0; i<256; i++)
    {
        float value = float(i)/255.;
        LinTable[i] = evalPixel(value);
    }

    return(LinTable);
}

Courbe Linearisation::getCourbe()
{
    return _courbe;
}


