
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
        glBindTexture(GL_TEXTURE_2D, mTextures[i].id());
        GLint textureLoc = glGetUniformLocation(mShader->id(), mTextures[i].name().c_str());
        glUniform1i(textureLoc, texUnit);
        ++texUnit;
    }

    mGeometry->drawGeometry(mShader->id());
}

void Object::loadImgTexture(const Image &image)
{
    Texture tex;
    tex.name("imgTex");
    int dimY = image.height();
    int dimX = image.width();
    int channel = (image.format() == GRAY)? 4 : 4;

    float* img;
    img = new float[dimX*dimY*channel];

    int i(0);
    for (int y = 0 ; y < dimY ; ++y)
    {
        for (int x = 0 ; x < dimX ; ++x)
        {
            Eigen::Vector4f rgba = image.pixel(x, y);
            for (int z = 0; z < channel; ++z)
            {
                img[i] = rgba(z);
                ++i;
            }
        }
    }
    GLuint tempId;
    glGenTextures(1,&tempId);
    tex.id(tempId);
    mTextures.push_back(tex);
    glBindTexture(GL_TEXTURE_2D, tex.id());

    if (image.format() == GRAY)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, img);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, img);
    }

    delete img;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::loadCurveTexture()
{
    Texture tex;
    tex.name("corTex");
    float* curve;
    curve = new float[256*4];

    for (unsigned int i = 0; i < 256; ++i)
    {
        for (unsigned j = 0; j < 3; ++j)
            curve[i*4 + j] = i/255.f;
        curve[i*4 + 3] = 1.f;
    }

    GLuint tempId;
    glGenTextures(1,&tempId);
    tex.id(tempId);
    mTextures.push_back(tex);
    glBindTexture(GL_TEXTURE_2D, tex.id());;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0,  GL_RGBA, GL_FLOAT, curve);

    delete curve;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindTexture(GL_TEXTURE_2D, 0);
}
