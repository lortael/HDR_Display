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

    virtual Image CPUprocess(Image const &img) = 0;

    virtual void GPUprocess(Image const &img);

private:

protected:

    std::vector<float> m_Parameters;

    void computeShaderParameters(Image const &img);

};

#endif //HDRPROCESS_H_INCLUDED
