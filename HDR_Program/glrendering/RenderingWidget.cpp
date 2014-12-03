#include "OpenGL.h"
#include <RenderingWidget.h>
#include <Eigen/Geometry>
#include <iostream>
#include <QKeyEvent>
#include <QImage>

using namespace Eigen;

RenderingWidget::RenderingWidget()
    :
//      #ifdef __APPLE__
//      QGLWidget(new Core3_2_context(QGLFormat::defaultFormat())),
//      #endif
      mCamera(),
      mCamPhy(0),
      mCamTheta(0),
      mCamDist(0.0001f),
      mCamLookAt(Vector3f::Zero()),
      mCamFov(M_PI_2),
      mObject(NULL),
      mMesh(NULL),
      mTextureId(0),
      mProgram(),
      mLastMousePos(),
      mTimer(new QTimer(this)),
      mMove(DISABLED),
      mFullscreen(WINDOW)
{
}

RenderingWidget::~RenderingWidget()
{
    delete mObject;
    delete mMesh;
}

void RenderingWidget::paintGL()
{
    GL_TEST_ERR;

    // update camera
    Vector3f cameraPos = mCamLookAt + mCamDist * Vector3f(
                std::sin(mCamPhy)*std::cos(mCamTheta),
                std::sin(mCamTheta),
                std::cos(mCamPhy)*std::cos(mCamTheta));
    mCamera.lookAt(cameraPos, mCamLookAt, Vector3f::UnitX());

    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mProgram.activate();

    GL_TEST_ERR;

//    glActiveTexture(GL_TEXTURE0 + 0);
//    glBindTexture(GL_TEXTURE_2D, mTextureId);
//    GLint textureLoc = glGetUniformLocation(mProgram.id(), "colorMap");
////    textureLoc = GL_TEXTURE_2D;
//    glUniform1i(textureLoc, 0);

//    glActiveTexture(GL_TEXTURE0 + 1);
//    glBindTexture(GL_TEXTURE_2D, mCorrectionId);
//    GLint texCorLoc = glGetUniformLocation(mProgram.id(), "texCor");
////    texCorLoc = GL_TEXTURE_2D;
//    glUniform1i(texCorLoc, 1);

    GL_TEST_ERR;

    GLint formatLoc = glGetUniformLocation(mProgram.id(), "formatImage");
    glUniform1i(formatLoc, mImage.format());
//    glUniform1i(formatLoc, 2);

    GL_TEST_ERR;

    // draw every objects
    for(ObjectList::const_iterator obj=mObjectList.begin(); obj!=mObjectList.end(); ++obj) {
        (*obj)->draw(mCamera);
    }

    GL_TEST_ERR;
}

void RenderingWidget::initializeGL()
{
    std::cout << "Using OpenGL version: \"" << glGetString(GL_VERSION) << "\"" << std::endl;
    std::cout << "OpenGL context: " << context()->format().majorVersion()
              << "." << context()->format().minorVersion()
              << " " << ((context()->format().profile() == QGLFormat::CoreProfile)? "Core":
                                                                                    (context()->format().profile() == QGLFormat::CompatibilityProfile)? "Compatibility":
                                                                                                                                                        "No profile")
              << std::endl;

    glClearColor(0.,0.,0.,0.);

    glEnable(GL_DEPTH_TEST);

    createScene();

    // Start a timer that redraw the scene every 16ms (around 60 fps).
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    mTimer->start(16);
}

void RenderingWidget::resizeGL(int width, int height)
{
    // configure the rendering target size (viewport)
    glViewport(0, 0, width, height);

    mCamera.setPerspective(mCamFov, float(width)/float(height), .01, 10., 2.);
}


void RenderingWidget::createScene()
{
    bool ok;

    // load the default shaders
    ok = mProgram.loadFromFiles(HDR_DIR"/shaders/simple.vert", HDR_DIR"/shaders/simple.frag");
    assert(ok);

    mMesh = new Mesh(HDR_DIR"/data/box.obj");
    mMesh->makeUnitary();
    mMesh->initBuffers();

    GL_TEST_ERR;

//    int dimY = mImage.height();
//    int dimX = mImage.width();
//    int channel = (mImage.format() == GRAY)? 4 : 4;

//    float* test;
//    test = new float[dimX*dimY*channel];

//    int i(0);
//    for (int y = 0 ; y < dimY ; ++y)
//    {
//        for (int x = 0 ; x < dimX ; ++x)
//        {
//            Eigen::Vector4f rgba = mImage.pixel(x, y);
//            for (int z = 0; z < channel; ++z)
//            {
//                test[i] = rgba(z);
//                ++i;
//            }
//        }
//    }

//    glGenTextures(1,&mTextureId);
//    glBindTexture(GL_TEXTURE_2D, mTextureId);

//    if (mImage.format() == GRAY)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, test);
//    }
//    else
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimX, dimY, 0,  GL_RGBA, GL_FLOAT, test);
//    }

//    delete test;

//    glGenerateMipmap(GL_TEXTURE_2D);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, 0);

//    float* test2;
//    test2 = new float[256*4];

//    for (unsigned int i = 0; i < 256; ++i)
//    {
//        for (unsigned j = 0; j < 3; ++j)
//            test2[i*4 + j] = i/255.f;
//        test2[i*4 + 3] = 1.f;
//    }

//    glGenTextures(1,&mCorrectionId);
//    glBindTexture(GL_TEXTURE_2D, mCorrectionId);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0,  GL_RGBA, GL_FLOAT, test2);

//    delete test2;

//    glGenerateMipmap(GL_TEXTURE_2D);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, 0);

    GL_TEST_ERR;

    mObject = new Object();
    mObject->attachShader(&mProgram);
    mObject->attachMesh(mMesh);
    mObject->loadImgTexture(mImage);
    mObject->loadCurveTexture();
    mObject->setTransformation(Matrix4f::Identity());

    mObjectList.push_back(mObject);

    GL_TEST_ERR;
}

void RenderingWidget::keyPressEvent(QKeyEvent * e)
{
    switch(e->key())
    {
    case Qt::Key_M:
    {
        mMove = (mMove == DISABLED)? ENABLED : DISABLED;
        break;
    }
    case Qt::Key_F:
    {
        if (mFullscreen != FULLSCREEN)
        {
            mFullscreen = FULLSCREEN;
            close();
            showFullScreen();
        }
        else if (mFullscreen == FULLSCREEN)
        {
            mFullscreen = WINDOW;
            close();
            show();
        }
        break;
    }
    case Qt::Key_C:
    {
        close();
        break;
    }
    case Qt::Key_Right:
        break;
    default:
        break;
    }

}

void RenderingWidget::mousePressEvent(QMouseEvent * e) {
    mLastMousePos = e->pos();
    grabMouse();
    e->accept();
}

void RenderingWidget::mouseReleaseEvent(QMouseEvent * e) {
    mLastMousePos = e->pos();
    releaseMouse();
    e->accept();
}

void RenderingWidget::mouseMoveEvent(QMouseEvent * e) {
    if (mMove == ENABLED) {
        if(e->buttons() & Qt::LeftButton) {
            mCamPhy += -float(e->x() - mLastMousePos.x()) / 256.;
            mCamTheta += float(e->y() - mLastMousePos.y()) / 256.;
            mCamTheta = std::min(M_PI_2-.001, std::max(-M_PI_2+0.001, double(mCamTheta)));
        }
        else if(e->buttons() & Qt::MiddleButton) {
            float offset = mCamDist * std::tan(mCamFov/width());
            Vector3f z = mCamera.getPosition()-mCamLookAt;
            Vector3f x = offset * (Vector3f::UnitY().cross(z)).normalized();
            Vector3f y = offset * (z.cross(x)).normalized();
            mCamLookAt += -x*(e->x() - mLastMousePos.x()) +
                    y*(e->y() - mLastMousePos.y());
        }
    }
    mLastMousePos = e->pos();
    e->accept();
}

void RenderingWidget::wheelEvent(QWheelEvent * e) {
    mCamDist *= (e->delta()>0)? 1./1.1: 1.1;
    e->accept();
}

#include <RenderingWidget.moc>
