#ifndef VECTOR3_H
#define VECTOR3_H

#include <ostream>

class Matrix4;

class Vector3
{
    friend class ThreeBSP;
    friend class Geometry;
    friend std::ostream& operator << (std::ostream& os, const Vector3 & v);

public:
    Vector3(float x = 0, float y = 0, float z = 0);
    Vector3* clone() const;
    float length() const;
    Vector3* add(const Vector3* other);
    Vector3* sub(const Vector3* other);
    Vector3* multiplyScalar(float t);
    Vector3* divideScalar(float t);
    Vector3* applyMatrix4(const Matrix4* matrix);
    Vector3 *subVectors(const Vector3* a, const Vector3* b);
    Vector3 * cross(const Vector3* v);
    Vector3* normalize();
    Vector3* copy(const Vector3* other);

protected:
    float x,y,z;
};



std::ostream& operator << (std::ostream& os, const Vector3 & v);

#endif // VECTOR3_H
