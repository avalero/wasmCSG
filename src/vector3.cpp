#include "vector3.h"

Vector3::Vector3(double x, double y, double z):
    x{x},
    y{y},
    z{z}
{

}

Vector3 *Vector3::clone()
{
    return new Vector3(x,y,z);
}

Vector3 *Vector3::add(Vector3 *other)
{
    x += other->x;
    y += other->y;
    z += other->z;
    return this;

}

Vector3 *Vector3::sub(Vector3 *other)
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
