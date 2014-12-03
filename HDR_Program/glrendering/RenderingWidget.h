
#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#include "OpenGL.h"

#include <list>

#include <Eigen/Geometry>

#include <QGLWidget>
#include <QApplication>
#include <QTimer>

#include "Camera.h"
#include "Object.h"
#include "../src/Image.h"

enum MOVEMENT {ENABLED = 0, DISABLED = 1};

enum SCREENMODE {FULLSCREEN = 0, WINDOW = 1};

class RenderingWidget : public QGLWidget
{
  Q_OBJECT

  typedef std::list<Object*> ObjectList;

  Camera mCamera;
  float mCamPhy;
  float mCamTheta;
  float mCamDist;
  Eigen::Vector3f mCamLookAt;
  float mCamFov;

  ObjectList mObjectList;
  Object* mObject;
  Mesh* mMesh;
  GLuint mTextureId;

  /* TODO 1.4: Sampler object */

  GLuint mSamplerId;
  GLenum mMinFilter;
  GLenum mMagFilter;

  // a shader program
  Shader mProgram;

  QPoint mLastMousePos;
  QTimer* mTimer;


  Image mImage;

  MOVEMENT mMove;
  SCREENMODE mFullscreen;

protected:

  /** This method is automatically called by Qt once the GL context has been created.
    * It is called only once per execution */
  virtual void initializeGL();

  /** This method is automatically called by Qt everytime the opengl windows is resized.
    * \param width the new width of the windows (in pixels)
    * \param height the new height of the windows (in pixels)
    *
    * This function must never be called directly. To redraw the windows, emit the updateGL() signal:
      \code
      emit updateGL();
      \endcode
    */
  virtual void resizeGL(int width, int height);

  /** This method is automatically called by Qt everytime the opengl windows has to be refreshed. */
  virtual void paintGL();

  /** This method is automatically called by Qt everytime a key is pressed */
  void keyPressEvent(QKeyEvent * e);

  void mousePressEvent(QMouseEvent * e);
  void mouseReleaseEvent(QMouseEvent * e);
  void mouseMoveEvent(QMouseEvent * e);
  void wheelEvent(QWheelEvent * e);

  /** Internal function to setup the 3D scene */
  virtual void createScene();

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  // default constructor
  RenderingWidget();
  ~RenderingWidget();
  void loadImage(Image const &image) {mImage = image;}
  SCREENMODE screenmode() {return mFullscreen;}
  void changeScreenMode(SCREENMODE mode) {mFullscreen = mode;}

};

#endif // RENDERINGWIDGET_H

