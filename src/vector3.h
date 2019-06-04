#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
public:
    Vector3(double x = 0, double y = 0, double z = 0);
    Vector3* clone();
    Vector3* add(Vector3* other);
    Vector3* sub(Vector3* other);
    Vector3* multiplyScalar(double t);

private:
    double x,y,z;
};

#endif // VECTOR3_H
