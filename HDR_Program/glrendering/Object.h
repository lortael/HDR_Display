#ifndef HDR_OBJECT_H
#define HDR_OBJECT_H

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
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
    void attachTexture(const Texture* texture);
    void setTransformation(const Eigen::Matrix4f& mat);

    void draw(const Camera& camera);

    void loadImgTexture(Image const& image, std::string texName);

    void updateTexture(Image const& image, std::string texName);

    void loadCurveTexture(const Linearisation &curve);

    void updateTargetTexture(Image const& image, std::string texName);

protected:

    const Shader* mShader;
    const Mesh* mGeometry;
    Eigen::Matrix4f mTransformation;

    std::vector<const Texture*> mTextures;
};

#endif
