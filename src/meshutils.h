#ifndef MESHUTILS_H
#define MESHUTILS_H

#include <vector>

class Triangle;
class Geometry;

std::vector<Triangle*> convertGeometryToTriangles(const Geometry* geometry);


#endif // MESHUTILS_H
