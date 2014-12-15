#include "OpenGL.h"
#include <RenderingWidget.h>
#include <Eigen/Geometry>
#include <iostream>
#include <QKeyEvent>
#include <QImage>

using namespace Eigen;

RenderingWidget::RenderingWidget()
    :
      mCamera(),
      mCamPhy(0),
      mCamTheta(0),
      mCamDist(0.0001f),
      mCamLookAt(Vector3f::Zero()),
      mCamFov(M_PI_2),
      mObject(NULL),
      mMesh(NULL),
      mProgram(),
      mLastMousePos(),
      mTimer(new QTimer(this)),
      mMove(DISABLED),
      mIsToneMapped(false),
      mIsBackPanel(false)
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

    GLint formatLoc = glGetUniformLocation(mProgram.id(), "tonemap");
    glUniform1i(formatLoc, int(mIsToneMapped));

    if (mParameters.size() > 0)
    {
        GLint paramLoc = glGetUniformLocation(mProgram.id(), "parameters");
        glUniform1fv(paramLoc, mParameters.size(), &mParameters[0]);
    }

    // draw every objects
//    for(ObjectList::const_iterator obj=mObjectList.begin(); obj!=mObjectList.end(); ++obj) {
//        (*obj)->draw(mCamera);
//    }

    mObject->draw(mCamera);

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
    ok = mProgram.loadFromFiles(mVertFilePath, mFragFilePath);
    assert(ok);

    mMesh = new Mesh(HDR_DIR"/data/box.obj");
    mMesh->makeUnitary();
    mMesh->initBuffers();

    GL_TEST_ERR;

    mObject = new Object();
    mObject->attachShader(&mProgram);
    mObject->attachMesh(mMesh);
    if(mIsBackPanel == false)
    {
//        mObject->loadImgTexture(mImagePSF, "imgTexPSF");
        mObject->loadImgTexture(mImage, "imgTexFront");
    }
    else
    {
        mObject->loadImgTexture(mImage, "imgTexBack");
        mObject->loadCurveTexture(mCurve);
    }
    mObject->setTransformation(Matrix4f::Identity());

//    mObjectList.push_back(mObject);

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

void RenderingWidget::updateTexture()
{
    makeCurrent();
    if(mIsBackPanel == false)
    {
//        mObject->loadImgTexture(mImagePSF, "imgTexPSF");
        mObject->updateTexture(mImage, "imgTexFront");
    }
    else
    {
        mObject->updateTexture(mImage, "imgTexBack");
    }
}

#include <RenderingWidget.moc>
