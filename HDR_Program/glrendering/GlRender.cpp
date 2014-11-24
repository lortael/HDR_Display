#include "GlRender.h"
#include <iostream>
#include <QImage>

using namespace std;

GlRender::GlRender()
{

}

GlRender::GlRender(Image const& img)
    : m_Image(img)
{

}

GlRender::~GlRender()
{
    glDeleteTextures(1, &m_TextureId);
}

void createScene(void)
{
    GlRender test;
    test.createCube();
}


void GlRender::initRender(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1600, 800);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Test");

    glutDisplayFunc(createScene);
    glutMainLoop();
}


void GlRender::resize (int w, int h)
{
//    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void GlRender::createCube(void)
{
    int nbVertex(18);
    m_Vertex = new float(nbVertex);
    m_Vertex[0] = -1.f;
    m_Vertex[1] = -1.f;
    m_Vertex[2] = 0.f;

    m_Vertex[3] = -1.f;
    m_Vertex[4] = 1.f;
    m_Vertex[5] = 0.f;

    m_Vertex[6] = 1.f;
    m_Vertex[7] = -1.f;
    m_Vertex[8] = 0.f;

    m_Vertex[9] = -1.f;
    m_Vertex[10] = 1.f;
    m_Vertex[11] = 0.f;

    m_Vertex[12] = 1.f;
    m_Vertex[13] = -1.f;
    m_Vertex[14] = 0.f;

    m_Vertex[15] = 1.f;
    m_Vertex[16] = 1.f;
    m_Vertex[17] = 0.f;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bool ok = m_Program.loadFromFiles(HDR_DIR"/shaders/simple.vert", HDR_DIR"/shaders/simple.frag");
    assert(ok);

    m_Program.activate();

//    glUseProgram(m_Program.id());

    glGenBuffers(1, &m_VertexId);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*nbVertex, m_Vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    int texcoord_loc   = glGetAttribLocation(m_ProgramId, "vtx_texcoord");
    if(texcoord_loc>=0)
    {
        glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(Eigen::Vector3f)));
        glEnableVertexAttribArray(texcoord_loc);
    }

    glDrawArrays(GL_TRIANGLES, 0, nbVertex);

    glDisableVertexAttribArray(0);
    if(texcoord_loc>=0)
    {
        glDisableVertexAttribArray(texcoord_loc);
    }

    glBindVertexArray(0);

    createTexture();

    glutSwapBuffers();
}

void GlRender::createTexture()
{
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    float pixelData[256*256*4];
//    pixelData = new float(256*256*4/*m_Image.width()*m_Image.height()*/);

    int i(0);
    for (unsigned int y = 0 ; y < 256/*m_Image.height()*/ ; ++y)
        for (unsigned int x = 0 ; x < 256/*m_Image.width()*/ ; ++x)
        {
//            Eigen::Vector4f rgba(0.f, 1.f, 0.f, 1.f) /*= m_Image.pixel(x, y)*/;
            float temp = i/(256.f*256.f*3.f);
            for (int z = 0; z < 4; ++z)
            {
                pixelData[i] = 255.f;
                ++i;
            }
        }

    QImage img(HDR_DIR"/data/brick_01.jpg");
    assert(!img.isNull());
    img = img.mirrored();


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,  GL_BGRA, GL_UNSIGNED_BYTE, img.bits());
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256/*m_Image.width()*/, 256/*m_Image.height()*/, 0, GL_RGBA, GL_FLOAT, pixelData);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLint textureLoc = glGetUniformLocation(m_Program.id(), "imageTex");
    glUniform1i(textureLoc, 1);

    glBindTexture(GL_TEXTURE_2D, 0);
//    delete pixelData;
}
