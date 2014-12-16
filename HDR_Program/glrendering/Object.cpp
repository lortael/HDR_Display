#include "Object.h"

Object::Object()
    : mShader(0), mGeometry(0), mTransformation(Eigen::Matrix4f::Identity())
{}

Object::~Object()
{
}

void Object::attachMesh(/*const*/ Mesh* mesh)
{
    mGeometry = mesh;
}

void Object::attachShader(const Shader* shader)
{
    mShader = shader;
}

void Object::attachTexture(const Texture* texture)
{
    mTextures.push_back(texture);
}

void Object::setTransformation(const Eigen::Matrix4f& mat)
{
    mTransformation = mat;
}

void Object::draw(const Camera &camera)
{
    mShader->activate();

    int viewMatrixLoc = mShader->getUniformLocation("view_matrix");
    int projectionMatrixLoc = mShader->getUniformLocation("projection_matrix");

    if(viewMatrixLoc >= 0) {
        Eigen::Matrix4f viewMatrix = camera.viewMatrix() * mTransformation;
        glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix.data());
    }
    if(projectionMatrixLoc >= 0)
        glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, camera.projectionMatrix().data());

    GL_TEST_ERR;

    int texUnit(0);
    for (unsigned int i = 0; i < mTextures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + texUnit);
        glBindTexture(GL_TEXTURE_2D, mTextures[i]->id());
        GLint textureLoc = glGetUniformLocation(mShader->id(), mTextures[i]->name().c_str());
        glUniform1i(textureLoc, texUnit);
        ++texUnit;
    }

    mGeometry->drawGeometry(mShader->id());
}

void Object::updateTargetTexture(Image const& image, std::string texName)
{
    for (unsigned int i = 0; i < mTextures.size(); ++i)
    {
        if (mTextures[i]->name() == texName)
            mTextures[i]->updateTexture(image);
    }
}
