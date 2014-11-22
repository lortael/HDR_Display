#ifndef GLRENDER_H_INCLUDED
#define GLRENDER_H_INCLUDED

#include "OpenGL.h"
#include <QGLWidget>
#include <QApplication>
#include <QTimer>

#include "../src/Image.h"
#include "Mesh.h"
#include "Shader.h"

class GlRender : public QGLWidget
{
    Q_OBJECT

public :

    GlRender();
    ~GlRender();

    virtual void initializeGL();

    virtual void resizeGL(int width, int height);

    virtual void paintGL();

    virtual void createScene();

    void createTexture(Image const & img);

    void keyPressEvent(QKeyEvent * e);


private:

protected:

    Mesh m_Mesh;
    Mesh m_QuadMesh;
    Shader m_Program;
    QTimer* m_Timer;

};

#endif //GLRENDER_H_INCLUDED
