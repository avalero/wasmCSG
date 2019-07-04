#ifndef FACE3_H
#define FACE3_H

#include <vector>
#include <ostream>

class Vector3;
class Triangle;
class Geometry;

// Based on THREE.Face3 class
class Face3
{
    friend class Geometry;
    friend std::vector<Triangle *> convertGeometryToTriangles(const Geometry *geometry);
    friend std::ostream & operator << (std::ostream& os, Face3 const & f);
public:
    Face3(unsigned long a, unsigned long b, unsigned long c, Vector3* normal = nullptr);
    Face3(unsigned long a, unsigned long b, unsigned long c, std::vector<Vector3*> vertexNormals = {});
    Face3* clone() const;
    Face3* copy(const Face3* source);

protected:
    unsigned long a,b,c;
    Vector3* normal;
    std::vector<Vector3*> vertexNormals;
};

std::ostream & operator << (std::ostream& os, Face3 const & f);

#endif // FACE3_H
