
#ifndef PGHP_OBJECT_H
#define PGHP_OBJECT_H

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Image.h"
#include "../src/correction/Linearisation.h"

class Object
{

public:
    Object();
    ~Object();

    void attachMesh(Mesh *mesh);
    void attachShader(const Shader* shader);
    void setTransformation(const Eigen::Matrix4f& mat);

    void draw(const Camera& camera);

    void loadImgTexture(Image const& image, std::string texName);

    void updateTexture(Image const& image, std::string texName);

    void loadCurveTexture(const Linearisation &curve);

protected:

    void computePSFImage(Image &img);

    Eigen::Vector4f convolutionKernel(unsigned int x, unsigned int y, Image const &img, Eigen::Matrix3i coeffs);

    struct Texture{
        GLuint textureId;
        std::string textureName;

        GLuint id() const {return textureId;}
        void id(GLuint id){textureId = id;}
        std::string name() const {return textureName;}
        void name(std::string name){textureName = name;}
    };

    const Shader* mShader;
    const Mesh* mGeometry;
    Eigen::Matrix4f mTransformation;

    std::vector<Texture> mTextures;
};

#endif
