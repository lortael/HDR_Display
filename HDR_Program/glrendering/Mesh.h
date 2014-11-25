// Copyright (C) 2008-2011 Gael Guennebaud <gael.guennebaud@inria.fr>

#ifndef _Mesh_h_
#define _Mesh_h_

#include <vector>
#include <string>
#include <Eigen/Core>

/** \class Mesh
  * A class to represent a 3D triangular mesh
  */
class Mesh
{
public:

    /** Default constructor loading a triangular mesh from the file \a filename */
    Mesh(const std::string& filename);

    /** Destructor */
    virtual ~Mesh();

    /** Loads a triangular mesh in the OFF format */
    void loadOFF(const std::string& filename);

    /** Loads a triangular mesh in the OBJ format */
    void loadOBJ(const std::string& filename);

    virtual void initBuffers();

    /** Send the mesh to OpenGL for drawing
      * \param prg_id id of the GLSL program used to draw the geometry */
    virtual void drawGeometry(int prg_id) const;

    void makeUnitary();
    void computeNormals();

protected:
    
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

    /** Represent a triangular face via its 3 vertex indices. */
    typedef Eigen::Vector3i FaceIndex;

    /** Represents a sequential list of vertices */
    typedef std::vector<Vertex> VertexArray;

    /** Represents a sequential list of triangles */
    typedef std::vector<FaceIndex> FaceIndexArray;

    /** The list of vertices */
    VertexArray mVertices;
    /** The list of face indices */
    FaceIndexArray mFaces;
    
    unsigned int mVertexBufferId; ///< the id of the BufferObject storing the vertex attributes
    unsigned int mIndexBufferId;  ///< the id of the BufferObject storing the faces indices
    unsigned int mVertexArrayId;  ///< the id of the VertexArray object
    //unsigned int mTexcoordBufferId;
    bool mIsInitialized;
};

#endif
