#include "Texture.h"

TextureImage::TextureImage()
{

}

TextureCorrection::TextureCorrection()
{

}


TextureImage::~TextureImage()
{
    glDeleteTextures(1, &mTexId);
}

TextureCorrection::~TextureCorrection()
{
    glDeleteTextures(1, &mTexId);
}

void TextureImage::loadTexture(Image const& image, std::string texName)
{
    mTexName = texName;

    Image temp(image);
    int dimY = temp.height();
    int dimX = temp.width();

    if (mTexName == "imgTexBack")
    {
        for (int y = 0 ; y < dimY ; ++y)
        {
            for (int x = 0 ; x < dimX ; ++x)
            {
                float l = temp.pixel(x, y)(0);
                l = sqrt(l);
                temp.setPixel(x, y, Eigen::Vector4f(l, l, l, 1.f));
            }
        }
        computePSFImage(temp);
    }
    else if (mTexName == "imgPSFFront")
    {
        temp.rgb2hsv();
        for (int y = 0 ; y < dimY ; ++y)
        {
            for (int x = 0 ; x < dimX ; ++x)
            {
                float r = temp.pixel(x, y)(0);
                float g = temp.pixel(x, y)(1);
                float b = temp.pixel(x, y)(2);
                temp.setPixel(x, y, Eigen::Vector4f(r, g, sqrt(b), 1.f));
            }
        }
        temp.hsv2rgb();
        computePSFImage(temp);
    }

    float* img;
    img = new float[dimX*dimY*4];

    int i(0);
    for (int y = 0 ; y < dimY ; ++y)
    {
        for (int x = 0 ; x < dimX ; ++x)
        {
            Eigen::Vector4f rgba = temp.pixel(x, y);
            for (int z = 0; z < 4; ++z)
            {
                img[i] = rgba(z);
                ++i;
            }
        }
    }
    glGenTextures(1,&mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, img);

    delete img;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureCorrection::loadTexture(Image const& image, std::string texName)
{
    mTexName = texName;

    float* curveTex;
    curveTex = new float[image.width()*4];

    for (unsigned int i = 0; i < 256; ++i)
    {
        for (unsigned int j = 0; j < 3; ++j)
            curveTex[i*4 + j] = image.pixel(i, 0)(j);
        curveTex[i*4 + 3] = 1.f;
    }

    glGenTextures(1,&mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0,  GL_RGBA, GL_FLOAT, curveTex);

    delete curveTex;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void TextureImage::updateTexture(Image const& image) const
{
    Image temp(image);
    int dimY = temp.height();
    int dimX = temp.width();

    if (mTexName == "imgTexBack")
    {
        for (int y = 0 ; y < dimY ; ++y)
        {
            for (int x = 0 ; x < dimX ; ++x)
            {
                float l = temp.pixel(x, y)(0);
                l = sqrt(l);
                temp.setPixel(x, y, Eigen::Vector4f(l, l, l, 1.f));
            }
        }
        computePSFImage(temp);
    }
    else if (mTexName == "imgPSFFront")
    {
        temp.rgb2hsv();
        for (int y = 0 ; y < dimY ; ++y)
        {
            for (int x = 0 ; x < dimX ; ++x)
            {
                float r = temp.pixel(x, y)(0);
                float g = temp.pixel(x, y)(1);
                float b = temp.pixel(x, y)(2);
                temp.setPixel(x, y, Eigen::Vector4f(r, g, sqrt(b), 1.f));
            }
        }
        temp.hsv2rgb();
        computePSFImage(temp);
    }

    float* img;
    img = new float[dimX*dimY*4];

    int i(0);
    for (int y = 0 ; y < dimY ; ++y)
    {
        for (int x = 0 ; x < dimX ; ++x)
        {
            Eigen::Vector4f rgba = temp.pixel(x, y);
            for (int z = 0; z < 4; ++z)
            {
                img[i] = rgba(z);
                ++i;
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, img);

    delete img;

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureCorrection::updateTexture(Image const& image) const
{

}

void TextureImage::computePSFImage(Image &img) const
{
    Eigen::Matrix3i coeffs3;
    coeffs3 << 1, 4, 1,
              4, 16, 4,
              1, 4, 1;

    Eigen::Matrix<float, 5 ,5> coeffs5;
    coeffs5 << 1, 4, 6, 4, 1,
            4, 16, 24, 16, 4,
            6, 24, 36, 24, 6,
            4, 16, 24, 16, 4,
            1, 4, 6, 4, 1;

    for (int y = 2 ; y < img.height()-2 ; ++y)
        for (int x = 2 ; x < img.width()-2 ; ++x)
            img.setPixel(x, y, convolutionKernel(x, y, img, coeffs5));
}

Eigen::Vector4f TextureImage::convolutionKernel(unsigned int x, unsigned int y, Image const &img, Eigen::Matrix3i coeffs) const
{
    Eigen::Vector4f sum(0.f, 0.f, 0.f, 1.f);

    for (unsigned int i = 0; i < 3; ++i)
        for (unsigned int j = 0; j < 3; ++j)
        {
            Eigen::Vector4f pix = img.pixel(x + i - 1, y + j - 1);
            float coeff = coeffs(i, j)/36.f;
            sum(0) += coeff*pix(0);
            sum(1) += coeff*pix(1);
            sum(2) += coeff*pix(2);
        }
    return sum;
}

Eigen::Vector4f TextureImage::convolutionKernel(unsigned int x, unsigned int y, Image const &img, Eigen::Matrix<float, 5, 5> coeffs) const
{
    Eigen::Vector4f sum(0.f, 0.f, 0.f, 1.f);

    for (unsigned int i = 0; i < 5; ++i)
        for (unsigned int j = 0; j < 5; ++j)
        {
            Eigen::Vector4f pix = img.pixel(x + i - 2, y + j - 2);
            float coeff = coeffs(i, j)/256.f;
            sum(0) += coeff*pix(0);
            sum(1) += coeff*pix(1);
            sum(2) += coeff*pix(2);
        }
    return sum;
}
