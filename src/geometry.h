#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <array>

class Face3;
class Vector2;
class Vector3;

class Geometry
{
public:
    Geometry(std::vector<Face3*> faces = {},
             std::vector< std::vector< std::vector< Vector2*> > > faceVertexUvs = {},
             std::vector< Vector3* > vertices = {});

    std::vector<Face3*> faces;
    std::vector< std::vector< std::vector< Vector2* > > > faceVertexUvs;
    std::vector< Vector3* > vertices;
};

#endif // GEOMETRY_H
