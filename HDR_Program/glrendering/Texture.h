#ifndef HDR_TEXTURE_H
#define HDR_TEXTURE_H

#include "Shader.h"
#include "Image.h"
#include "../src/correction/Linearisation.h"

class Texture
{
public:

    virtual GLuint id() const {return mTexId;}
    virtual void setId(GLuint id){mTexId = id;}
    virtual std::string name() const {return mTexName;}
    virtual void setName(std::string name){mTexName = name;}

private:

protected:

    GLuint mTexId;
    std::string mTexName;

};

class TextureImage : public Texture
{
public:

    TextureImage();

    ~TextureImage();

    void loadImgTexture(Image const& image, std::string texName);

    void updateTexture(Image const& image);

private:

protected:

    void computePSFImage(Image &img);

    Eigen::Vector4f convolutionKernel(unsigned int x, unsigned int y, Image const &img, Eigen::Matrix3i coeffs);

};

class TextureCorrection : public Texture
{
public:

    TextureCorrection();

    ~TextureCorrection();

    void loadCurveTexture(const Linearisation &curve);

private:

protected:

};

#endif
