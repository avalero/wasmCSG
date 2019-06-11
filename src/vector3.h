#ifndef VECTOR3_H
#define VECTOR3_H

class Matrix4;

class Vector3
{
    friend class ThreeBSP;
public:
    Vector3(double x = 0, double y = 0, double z = 0);
    Vector3* clone() const;
    Vector3* add(const Vector3* other);
    Vector3* sub(const Vector3* other);
    Vector3* multiplyScalar(double t);
    Vector3* applyMatrix4(const Matrix4* matrix);

protected:
    double x,y,z;
};

#endif // VECTOR3_H
