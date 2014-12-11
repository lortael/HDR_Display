#include "Object.h"

Object::Object()
    : mShader(0), mGeometry(0), mTransformation(Eigen::Matrix4f::Identity())
{}

Object::~Object()
{
    for (unsigned int i = 0; i < mTextures.size(); ++i)
    {
        glDeleteTextures(1, &mTextures[i].textureId);
    }
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

void Object::loadImgTexture(const Image &image, std::string texName)
{
    Texture tex;
    tex.name(texName);
    int dimY = image.height();
    int dimX = image.width();

    float* img;
    img = new float[dimX*dimY*4];

    int i(0);
    for (int y = 0 ; y < dimY ; ++y)
    {
        for (int x = 0 ; x < dimX ; ++x)
        {
            Eigen::Vector4f rgba = image.pixel(x, y);
            for (int z = 0; z < 4; ++z)
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, img);

    delete img;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::loadCurveTexture(const Linearisation &curve)
{
    Texture tex;
    tex.name("corTex");

    float* curveTex;
    curveTex = new float[256*4];

    for (unsigned int i = 0; i < 256; ++i)
    {
        for (unsigned int j = 0; j < 3; ++j)
            curveTex[i*4 + j] = curve.getCoeff(i);
        curveTex[i*4 + 3] = 1.f;
    }

    GLuint tempId;
    glGenTextures(1,&tempId);
    tex.id(tempId);
    mTextures.push_back(tex);
    glBindTexture(GL_TEXTURE_2D, tex.id());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0,  GL_RGBA, GL_FLOAT, curveTex);

    delete curveTex;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void Object::updateTexture(const Image& image, std::string texName)
{
    int i(0);
    bool isImg(false);
    while (isImg == false && i < mTextures.size())
    {
        if (mTextures[i].name() == texName)
            isImg = true;
        else
            ++i;
    }

    unsigned int dimY = image.height();
    unsigned int dimX = image.width();

    float* img;
    img = new float[dimX*dimY*4];

    int j(0);
    for (int y = 0 ; y < dimY ; ++y)
    {
        for (int x = 0 ; x < dimX ; ++x)
        {
            Eigen::Vector4f rgba = image.pixel(x, y);
            for (int z = 0; z < 4; ++z)
            {
                img[j] = rgba(z);
                ++j;
            }
        }
    }

    GLuint tempId;
    glGenTextures(1,&tempId);
    mTextures[i].id(tempId);
    glBindTexture(GL_TEXTURE_2D, mTextures[i].id());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, img);

    delete img;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindTexture(GL_TEXTURE_2D, 0);
}
