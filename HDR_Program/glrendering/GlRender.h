#ifndef GLRENDER_H_INCLUDED
#define GLRENDER_H_INCLUDED

#include "OpenGL.h"
#include "Image.h"
#include "Shader.h"

class GlRender
{

public :

    GlRender();

    ~GlRender();

    GlRender(Image const& img);

    void initRender(int argc, char *argv[]);

    void resize (int w, int h);

    void createCube(void);

    void createTexture();

private:

protected:

    float* m_Vertex;
    GLuint m_VertexId;

    GLuint m_ProgramId;
    Shader m_Program;

    GLuint m_TextureId;

    Image m_Image;

    typedef Eigen::Vector3f Vector3;

    /** Represents a vertex of the mesh */
    struct Vertex
    {
      Vertex()
        : position(Eigen::Vector3f::Zero()), normal(Eigen::Vector3f::Zero()), texcoord(Eigen::Vector2f::Zero())
      {}
      Vertex(const Eigen::Vector3f& pos)
        : position(pos), normal(Eigen::Vector3f::Zero()), texcoord(Eigen::Vector2f::Zero())
      {}
      Eigen::Vector3f position;
      Eigen::Vector3f normal;
      Eigen::Vector2f texcoord;
    };

};

#endif //GLRENDER_H_INCLUDED
