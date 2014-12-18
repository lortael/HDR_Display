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
     * @param img, the Image to be treated.
     * */
    /// /!\ Deprecated, should be used only if no GPU are available, or OpenGL version is below 3.0.
    /// @see displayImageGL()
    virtual Image CPUprocess(Image const &img) = 0;

    /**
     * @brief apply HDR process on GPU. Unused for the moment. To complete for further GPU processing than tone-mapping shader parameters.
     * @param img, the Image to be treated.
     * */
    virtual void GPUprocess(Image const &img);

private:

protected:

    //Shaders parameters.
    std::vector<float> m_Parameters;

    /**
     * @brief computes all the necessary shader parameters, used mainly for tone-mapping.
     * @param img,the Image on which parameters are computed.
     * */
    void computeShaderParameters(Image const &img);

};

#endif //HDRPROCESS_H_INCLUDED
