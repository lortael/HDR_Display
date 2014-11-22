#include "GlRender.h"

GlRender::GlRender()
{

}

void GlRender::glEnable2D()
{
    int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}

void GlRender::glDisable2D()
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void GlRender::RenderScene()
{
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glEnable2D();
    glBegin(GL_TRIANGLES);
      glColor3ub(255, 0, 0);
        glVertex2d(0, 0);
      glColor3ub(0, 255, 0);
        glVertex2d(100,0);
      glColor3ub(0, 0, 255);
        glVertex2d(50, 50);
    glEnd();
  glDisable2D();
}
