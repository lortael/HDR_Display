#include "HDRProcess.h"

void HDRProcess::GPUprocess(const Image &img)
{
    computeShaderParameters(img);
}

void HDRProcess::computeShaderParameters(const Image &img)
{
    using namespace Eigen;

    float max(0.f), min(1000.f), Lmean(0.f);
    Vector3f channelAv(0.f, 0.f, 0.f);
    for (int y = 0; y < img.height(); ++y)
        for (int x = 0; x < img.width(); ++x)
        {
            float r = 255*img.pixel(x, y)(0);
            float g = 255*img.pixel(x, y)(1);
            float b = 255*img.pixel(x, y)(2);

            float l = 0.2125*r + 0.7154*g + 0.0721*b;

            max = (l > max)? l : max;
            min = (l < min)? l : min;

            channelAv = channelAv + Vector3f(r/(img.height()*img.width()), g/(img.height()*img.width()), b/(img.height()*img.width()));
        }

    Lmean = 0.2125*channelAv(0) + 0.7154*channelAv(1) + 0.0721*channelAv(2);
    float logMean = log(Lmean);
    float logMax = log(max);
    float logMin = log((min < 0.01f) ? 0.01f : min);

    float k = (logMax - logMean)/(logMax - logMin);
    float m = 0.3f + 0.7f*pow(k, 1.4);

    float fp(-5.f), fparam;
    fparam = exp(-fp);

    m_Parameters.push_back(channelAv(0));
    m_Parameters.push_back(channelAv(1));
    m_Parameters.push_back(channelAv(2));
    m_Parameters.push_back(max);
    m_Parameters.push_back(Lmean);
    m_Parameters.push_back(fparam);
    m_Parameters.push_back(m);
}
