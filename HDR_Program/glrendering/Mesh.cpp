// Copyright (C) 2008-2011 Gael Guennebaud <gael.guennebaud@inria.fr>


#include "Mesh.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <limits>

#include <QCoreApplication>
#include <Eigen/Geometry>

using namespace Eigen;

Mesh::Mesh()
  : mIsInitialized(false)
{
}

Mesh::Mesh(const std::string& filename)
  : mIsInitialized(false)
{
  std::string ext = filename.substr(filename.size()-3,3);
  if(ext=="off" || ext=="OFF")
    loadOFF(filename);
  else
    std::cerr << "Mesh: extension \'" << ext << "\' not supported." << std::endl;
}

void Mesh::loadOFF(const std::string& filename)
{
  std::ifstream in(filename.c_str(),std::ios::in);
  if(!in)
  {
    std::cerr << "File not found " << filename << std::endl;
    return;
  }

  std::string header;
  in >> header;

  // check the header file
  if(header != "OFF")
  {
      std::cerr << "Wrong header = " << header << std::endl;
      return;
  }

  int nofVertices, nofFaces, inull;
  int nb;
  Eigen::Vector3i ids;
  Vector3 v;

  in >> nofVertices >> nofFaces >> inull;

  std::vector<Vector3> vertices;

  for(int i=0 ; i<nofVertices ; ++i)
  {
      in >> v.x() >> v.y() >> v.z();
      vertices.push_back(v);
  }

  for(int i=0 ; i<nofFaces ; ++i)
  {
      in >> nb >> ids[0] >> ids[1] >> ids[2];
      assert(nb==3);
      for(int k=0; k<3; ++k)
        mVertices.push_back(vertices[ids[k]]);
  }

  in.close();
}

Mesh::~Mesh()
{
  if(mIsInitialized)
  {
    glDeleteBuffers(1,&mVertexBufferId);
  }
}

void Mesh::makeUnitary()
{
  // computes the lowest and highest coordinates of the axis aligned bounding box,
  // which are equal to the lowest and highest coordinates of the vertex positions.
  Eigen::Vector3f lowest, highest;
  lowest.fill(std::numeric_limits<float>::max());   // "fill" sets all the coefficients of the vector to the same value
  highest.fill(-std::numeric_limits<float>::max());

  for(std::vector<Vector3>::iterator v_iter = mVertices.begin() ; v_iter!=mVertices.end() ; ++v_iter)
  {
    // - v_iter is an iterator over the elements of mVertices,
    //   an iterator behaves likes a pointer, it has to be dereferenced (*v_iter, or v_iter->) to access the referenced element.
    // - Here the .aray().min(_) and .array().max(_) operators work per component.
    //
    lowest  = lowest.array().min(v_iter->array());
    highest = highest.array().max(v_iter->array());
  }

  // appliquer une transformation à tous les sommets de mVertices de telle sorte
  // que la boite englobante de l'objet soit centrée en (0,0,0)  et que sa plus grande dimension soit de 1
  Eigen::Vector3f center = (lowest+highest)/2.0;
  float m = (highest-lowest).maxCoeff();
  for(std::vector<Vector3>::iterator v_iter = mVertices.begin() ; v_iter!=mVertices.end() ; ++v_iter)
    (*v_iter) = ((*v_iter) - center) / m;
}

void Mesh::drawGeometry(int prg_id)
{
  if(!mIsInitialized)
  {
    mIsInitialized = true;
    // this is the first call to drawGeometry
    // => create the BufferObjects and copy the related data into them.
    glGenBuffers(1,&mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3)*mVertices.size(), mVertices[0].data(), GL_STATIC_DRAW);

    glGenVertexArrays(1,&mVertexArrayId);
  }

  // bind the vertex array
  glBindVertexArray(mVertexArrayId);

  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

  int vertex_loc   = glGetAttribLocation(prg_id, "vtx_position");

  // specify the vertex data
  if(vertex_loc>=0)
  {
    glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
    glEnableVertexAttribArray(vertex_loc);
  }
  else
    glDisableVertexAttribArray(vertex_loc);

  // send the geometry
  glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

  // release the vertex array
  glBindVertexArray(0);
}



