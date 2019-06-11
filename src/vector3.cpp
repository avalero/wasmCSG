#include "vector3.h"
#include "matrix4.h"
#include <array>

Vector3::Vector3(double x, double y, double z):
    x{x},
    y{y},
    z{z}
{

}

Vector3 *Vector3::clone() const
{
    return new Vector3(x,y,z);
}

Vector3 *Vector3::add(const Vector3 *other)
{
    x += other->x;
    y += other->y;
    z += other->z;
    return this;

}

Vector3 *Vector3::sub(const Vector3 *other)
{
    x -= other->x;
    y -= other->y;
    z -= other->z;
    return this;

}

Vector3 *Vector3::multiplyScalar(double t)
{
    x *= t;
    y *= t;
    z *= t;
    return this;

}

Vector3 *Vector3::applyMatrix4(const Matrix4 *m)
{
    double _x = x;
    double _y = y;
    double _z = z;
    std::array<double, 16>* e = m->elements;

    double w = 1 / ( e->at(3) * x + e->at(7) * y + e->at(11) * z + e->at(15) );

    x = ( e->at(0) * _x + e->at(4) * _y + e->at(8) * _z + e->at(12) ) * w;
    y = ( e->at(1) * _x + e->at(5) * _y + e->at(9) * _z + e->at(13) ) * w;
    z = ( e->at(2) * _x + e->at(6) * _y + e->at(10) * _z + e->at(14) ) * w;

    return this;
}
