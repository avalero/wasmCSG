#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <array>

class Face3;
class Vector2;
class Vector3;
class BufferGeometry;

class Geometry
{
public:
    Geometry(std::vector<Face3*> faces = {},
             std::vector< std::vector< std::vector< Vector2*> > > faceVertexUvs = {},
             std::vector< Vector3* > vertices = {});

    Geometry(const std::vector<float> &_vertices, const std::vector<float> &_normals, const std::vector<float> &_position);

    void addFace(unsigned long int a, unsigned long int b, unsigned long int c, const std::vector<float>& normals);
    void computeFaceNormals();

    BufferGeometry* toBufferGeometry() const;

    std::vector<Face3*> faces;
    std::vector< std::vector< std::vector< Vector2* > > > faceVertexUvs;
    std::vector< Vector3* > vertices;
};

#endif // GEOMETRY_H
