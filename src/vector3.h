#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
public:
    Vector3();
    Vector3* clone();
    Vector3* add(Vector3* other);
    Vector3* sub(Vector3* other);
    Vector3* multiplyScalar(float t);
};

#endif // VECTOR3_H
