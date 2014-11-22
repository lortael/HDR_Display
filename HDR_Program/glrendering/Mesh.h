#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <vector>
#include <string>
#include <Eigen/Core>

/** \class Mesh
  * A class to represent a 3D triangular mesh
  */
class Mesh
{
public:

    /** Default constructor */
    Mesh();

    /** A constructor loading a triangular mesh from the file \a filename */
    Mesh(const std::string& filename);

    /** Destructor */
    virtual ~Mesh();

    /** Loads a triangular mesh in the OFF format */
    void loadOFF(const std::string& filename);

    /** Send the mesh to OpenGL for drawing
      * \param prg_id id of the GLSL program used to draw the geometry */
    virtual void drawGeometry(int prg_id) ;

    void makeUnitary();

protected:

    typedef Eigen::Vector3f Vector3;

    /** The list of vertices */
    std::vector<Vector3> mVertices;

    unsigned int mVertexBufferId; ///< the id of the BufferObject storing the vertex attributes
    unsigned int mVertexArrayId;  ///< the id of the VertexArray object
    bool mIsInitialized;
};

#endif //MESH_H_INCLUDED
