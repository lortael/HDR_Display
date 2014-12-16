
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
#include "../src/correction/Linearisation.h"

enum MOVEMENT {ENABLED = 0, DISABLED = 1};
enum FORMAT {BACK = 0, FRONT = 1, TONEMAPPED = 2};

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
  Texture* mTexture;
  Texture* mTexturePSF;
  Texture* mCorrection;
  Image mImage;
  Linearisation mCurve;

  // a shader program
  Shader mProgram;
  std::string mVertFilePath;
  std::string mFragFilePath;
  std::vector<float> mParameters;

  QPoint mLastMousePos;
  QTimer* mTimer;

  MOVEMENT mMove;
  bool mIsToneMapped;
  bool mIsBackPanel;

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

  /*******************************************/
  /*All below
   *
   * */
  void loadImage(Image const &image) {mImage = image;}
  void loadCurve(Linearisation const &curve) {mCurve = curve;}
  void loadShaders(const std::string& fileV, const std::string& fileF) {mVertFilePath = fileV; mFragFilePath = fileF;}

  void toggleToneMapping() {mIsToneMapped = true;}
  void toggleHDRDisplay() {mIsToneMapped = false;}

  void isBackPanel() {mIsBackPanel = true;}

  void updateTextures();

  void setToneMappingParameters(std::vector<float> param) {mParameters = param;}
};

#endif // RENDERINGWIDGET_H

