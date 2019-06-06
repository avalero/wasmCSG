#ifndef FACE3_H
#define FACE3_H

#include <vector>

class Vector3;

// Based on THREE.Face3 class
class Face3
{
    friend class ThreeBSP;
public:
    Face3(unsigned long a, unsigned long b, unsigned long c, Vector3* normal = nullptr);
    Face3(unsigned long a, unsigned long b, unsigned long c, std::vector<Vector3*> vertexNormals = {});
    Face3* clone() const;
    Face3* copy(Face3* source);

protected:
    unsigned long a,b,c;
    Vector3* normal;
    std::vector<Vector3*> vertexNormals;
};

#endif // FACE3_H
