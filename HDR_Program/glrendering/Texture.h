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

    virtual void loadTexture(Image const& image, std::string texName) = 0;

    virtual void updateTexture(Image const& image) const = 0;

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

    void loadTexture(Image const& image, std::string texName);

    void updateTexture(Image const& image) const;

private:

protected:

    void computePSFImage(Image &img) const;

    Eigen::Vector4f convolutionKernel(unsigned int x, unsigned int y, Image const &img, Eigen::Matrix3i coeffs) const;

};

class TextureCorrection : public Texture
{
public:

    TextureCorrection();

    ~TextureCorrection();

    void loadTexture(Image const& image, std::string texName);

    void updateTexture(Image const& image) const;

private:

protected:

};

#endif
