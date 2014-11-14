#include "ImageIO.h"
#include <QImage>
using namespace cv;
using namespace eigen;

void loadImg(Image& dst, std::string const filePath)
{
    int m_sizeX, m_sizeY;
    if (filePath.endsWith(".hdr"))
    {
        FILE* f = fopen(filePath.toStdString().c_str(), "rb");

        // Read image header
        if(RGBE_ReadHeader(f, &m_sizeX, &m_sizeY, 0)!=0){
            return false;
        }
        float* m_image;
        m_image = new float[sizeof(float)*3*m_sizeX*m_sizeY];
        // Read image data
        if(RGBE_ReadPixels_RLE(f, reinterpret_cast<float*>(m_image), m_sizeX, m_sizeY)!=0){
            return false;
        }
        return true;
    }

    QImage image;
    if (image.load(filePath)){
        dst.setHeight(m_sizeY);
        dst.setWidth(m_sizeX);
        dst.initImage();
        for(int x = 0; x < m_sizeX; ++x)
            for(int y = 0; y < m_sizeY; ++y)
            {
                QRgb c = image.pixel(x,y);
                m_image[ 3 * ( x + m_sizeX * y )    ] = qRed(c)/255.f;
                m_image[ 3 * ( x + m_sizeX * y ) + 1] = qGreen(c)/255.f;
                m_image[ 3 * ( x + m_sizeX * y ) + 2] = qBlue(c)/255.f;
                dst.setPixel(x, y, Vector3f(qRed(c)/255.f, qGreen(c)/255.f, qBlue(c)/255.f));
            }
        return true;
    }
    qWarning("Could not open: %s", qPrintable(filename));
    return false;
}

void saveImg(Image const src, std::string const filePath) const
{
    for(int x = 0; x < src.width(); ++x)
        for(int y = 0; y < src.height(); ++y)
            std::cout << src.pixel(x, y).transpose << std::endl;
}

Image toneMapping(Image const src)
{

}
