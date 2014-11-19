#include "GLRender.h"

#include "GLPrimitives.h"

#include <Eigen/Geometry>
#include <iostream>
#include <QKeyEvent>
#include <QFileDialog>

GLRender::GLRender()
{
    mDrawCamera = false;
}

GLRender::~GLRender()
{

}

void GLRender::initializeGL()
{
    makeCurrent();
    GL_TEST_ERR;
    std::cout << "Using OpenGL version: \"" << glGetString(GL_VERSION) << "\"" << std::endl;
    std::cout << "OpenGL context: " << context()->format().majorVersion()
              << "." << context()->format().minorVersion()
              << " " << ((context()->format().profile() == QGLFormat::CoreProfile)? "Core":
                         (context()->format().profile() == QGLFormat::CompatibilityProfile)? "Compatibility":
                         "No profile")
              << std::endl;
}

void GLRender::resizeGL(int width, int height)
{
    mGLCamera.setViewport(width,height);
}

void GLRender::paintGL()
{
    makeCurrent();
    GL_TEST_ERR;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure the rendering target size (viewport)
    glViewport(0, 0, mGLCamera.vpWidth(), mGLCamera.vpHeight());

}

void GLRender::keyPressEvent(QKeyEvent * e)
{

}

void GLRender::loadScene()
{

}
