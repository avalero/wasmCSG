#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
    friend class ThreeBSP;
public:
    Vector3(double x = 0, double y = 0, double z = 0);
    Vector3* clone() const;
    Vector3* add(const Vector3* other);
    Vector3* sub(const Vector3* other);
    Vector3* multiplyScalar(double t);

protected:
    double x,y,z;
};

#endif // VECTOR3_H
