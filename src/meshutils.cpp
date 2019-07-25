#include "meshutils.h"
#include "triangle.h"
#include "face3.h"
#include "geometry.h"
#include "vector3.h"

#include <iostream>

std::vector<Triangle *> convertGeometryToTriangles(const Geometry *geometry)
{
    std::vector<Triangle*> triangles;

    std::vector<Face3*> faces = geometry->faces;
    std::vector<Vector3*> vertices = geometry->vertices;

    for(unsigned long int i = 0; i < faces.size(); i++){
        Face3* face = faces.at(i);
        Vector3* a = vertices.at(face->a);
        Vector3* b = vertices.at(face->b);
        Vector3* c = vertices.at(face->c);
        Triangle* triangle = new Triangle(a,b,c);
        triangles.push_back(triangle);
    }

    return triangles;
}
