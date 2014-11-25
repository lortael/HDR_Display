
#ifndef PGHP_OBJECT_H
#define PGHP_OBJECT_H

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

class Object
{
public:
    Object();

    void attachMesh(Mesh *mesh);
    void attachShader(const Shader* shader);
    void setTransformation(const Eigen::Matrix4f& mat);

    void draw(const Camera& camera);

protected:
    const Shader* mShader;
    const Mesh* mGeometry;
    Eigen::Matrix4f mTransformation;
};

#endif
