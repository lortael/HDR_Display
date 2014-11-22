#include "GlRender.h"

#include <Eigen/Geometry>
#include <iostream>
#include <QKeyEvent>

using namespace Eigen;

GlRender::GlRender()
  :
    m_Mesh(),
    m_Program(),
    m_Timer(new QTimer(this))
{
}

GlRender::~GlRender()
{

}

void GlRender::paintGL()
{
    GL_TEST_ERR;

    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // activate the shader
    m_Program.activate();

    Eigen::Matrix4f M;
    M << 1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1;
    GLint IdentityLoc = glGetUniformLocation(m_Program.id(), "mTransformation");
    glUniformMatrix4fv(IdentityLoc, 1, 0, M.data());
    m_Mesh.drawGeometry( m_Program.id() );

    // check opengl errors
    GL_TEST_ERR;

  //  connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
  //  mTimer.start(33);
}

void GlRender::initializeGL()
{
    std::cout << "Using OpenGL version: \"" << glGetString(GL_VERSION) << "\"" << std::endl;
    std::cout << "OpenGL context: " << context()->format().majorVersion()
              << "." << context()->format().minorVersion()
              << " " << ((context()->format().profile() == QGLFormat::CoreProfile)? "Core":
                         (context()->format().profile() == QGLFormat::CompatibilityProfile)? "Compatibility":
                         "No profile")
              << "\n";

    glClearColor(0.,0.,0.,0.);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    createScene();

    // Start a timer that redraw the scene every 16ms (around 60 fps).
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    m_Timer->start(16);
}

void GlRender::createScene()
{
  // load the default shaders
  m_Program.loadFromFiles(HDR_DIR"/shaders/simple.vert", HDR_DIR"/shaders/simple.frag");

//  m_Mesh.loadOFF(HDR_DIR"/data/tw.off");
//  m_Mesh.makeUnitary();

  m_Mesh.loadOFF(HDR_DIR"/data/quad.off");
  m_Mesh.makeUnitary();

//  m_Mesh.loadOFF(HDR_DIR"/data/sphere.off");
//  m_Mesh.makeUnitary();

  GL_TEST_ERR;
}

void GlRender::keyPressEvent(QKeyEvent * e)
{
  switch(e->key())
  {
    case Qt::Key_Up:
      break;
    case Qt::Key_Down:
      break;
    case Qt::Key_Left:
      break;
    case Qt::Key_Right:
      break;
    default:
      break;
  }

}

void GlRender::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GlRender::createTexture(Image const & img)
{
//    assert(!img.isNull());
////    img = img.mirrored(); // miroir vertical pour être compatible avec OpenGL

//    /* TODO 1.3: charger la texture dans OpenGL
//     *   Utiliser la variable mTextureId pour cela (déjà déclarée) */
//    glGenTextures(1,&mTextureId);
//    glBindTexture(GL_TEXTURE_2D, mTextureId);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,  GL_BGRA, GL_UNSIGNED_BYTE, img.bits());

//    /* TODO 1.3: générer les mipmaps */
//    glGenerateMipmap(GL_TEXTURE_2D);

//    /* TODO 1.3: définir les paramètres de filtrages */
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//    /* TODO 1.4: Créer un sampler object */
//    glGenSamplers(1, &mSamplerId);
//    glSamplerParameteri(mSamplerId, GL_TEXTURE_MIN_FILTER, mMinFilter);
//    glSamplerParameteri(mSamplerId, GL_TEXTURE_MAG_FILTER, mMagFilter);
//    //glBindSampler(GL_TEXTURE_2D, mSamplerId);



//    glSamplerParameteri(mSamplerId, GL_TEXTURE_MIN_FILTER, mMinFilter);
//    glSamplerParameteri(mSamplerId, GL_TEXTURE_MAG_FILTER, mMagFilter);
//    glBindSampler(0, mSamplerId);
//    GLint samplerLoc = glGetUniformLocation(mProgram.id(), "colorMap");
//    //glUniform1f(samplerLoc, 0);
//    samplerLoc = GL_TEXTURE_2D;

//    /* TODO 1.3: lier une texture pour l'affichage */
//    //glBindTexture(GL_TEXTURE_2D, mTextureId);
//    GLint textureLoc = glGetUniformLocation(mProgram.id(), "colorMap");
//    //glUniform1f(textureLoc, 0);
//    textureLoc = GL_TEXTURE_2D;
}
