/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
 * */

#ifndef HDRPROCESS_H_INCLUDED
#define HDRPROCESS_H_INCLUDED

#include "Image.h"

class HDRProcess
{
public :

    /**
     * @brief apply HDR process on CPU. See inherited class.
     * @param the Image to be displayed.
     * */
    virtual Image CPUprocess(Image const &img) = 0;

    /**
     * @brief apply HDR process on GPU. Unused for the moment.
     * @param the Image to be displayed.
     * */
    virtual void GPUprocess(Image const &img);

private:

protected:

    //Shaders parameters.
    std::vector<float> m_Parameters;

    /**
     * @brief computes all the necessary shader parameters, used mainly for tone-mapping.
     * @param the Image on which parameters are computed.
     * */
    void computeShaderParameters(Image const &img);

};

#endif //HDRPROCESS_H_INCLUDED
