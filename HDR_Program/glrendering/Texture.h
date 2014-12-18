/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Classes to manage texture for images and correction.
 * */

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

    /**
     * @brief loads an image (or an array stored in an image) into a texture, given its name.
     * @param image, the Image to be sent as texture.
     * @param texName, the uniform that will be sent into GLSL.
     * */
    virtual void loadTexture(Image const& image, std::string texName) = 0;

    /**
     * @brief changes the image stored in the current texture.
     * @param image, the new image to store.
     * */
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
