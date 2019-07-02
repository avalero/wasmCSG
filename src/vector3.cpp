#include "vector3.h"
#include "matrix4.h"
#include <array>
#include <math.h>
#include <string>
#include <iostream>

Vector3::Vector3(float x, float y, float z):
    x{x},
    y{y},
    z{z}
{

}

Vector3 *Vector3::clone() const
{
    return new Vector3(x,y,z);
}

float Vector3::length() const
{
    return sqrt(x*x + y*y +z*z);
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

Vector3 *Vector3::multiplyScalar(float t)
{
    x *= t;
    y *= t;
    z *= t;
    return this;

}

Vector3 *Vector3::divideScalar(float t)
{
    if(t <= 0.000001){
        std::cout << "divideScalar: Cannot be divyded by 0" << std::endl;
        throw std::string{"Cannot dived by 0"};
    }
    x /= t;
    y /= t;
    z /= t;

    return this;
}

Vector3 *Vector3::applyMatrix4(const Matrix4 *m)
{
    float _x = x;
    float _y = y;
    float _z = z;
    std::array<float, 16>* e = m->elements;

    float w = 1 / ( e->at(3) * x + e->at(7) * y + e->at(11) * z + e->at(15) );

    x = ( e->at(0) * _x + e->at(4) * _y + e->at(8) * _z + e->at(12) ) * w;
    y = ( e->at(1) * _x + e->at(5) * _y + e->at(9) * _z + e->at(13) ) * w;
    z = ( e->at(2) * _x + e->at(6) * _y + e->at(10) * _z + e->at(14) ) * w;

    return this;
}

Vector3 *Vector3::subVectors(const Vector3 *a, const Vector3 *b)
{
    this->x = a->x - b->x;
    this->y = a->y - b->y;
    this->z = a->z - b->z;

    return this;
}

Vector3 *Vector3::cross(const Vector3 *b)
{
    float ax = x; float ay = y; float az = z;
    float bx = b->x; float by = b->y; float bz = b->z;
    x = ay * bz - az * by;
    y = az * bx - ax * bz;
    z = ax * by - ay * bx;

    return this;
}

Vector3 *Vector3::normalize()
{
    return divideScalar(length());
}

Vector3 *Vector3::copy(const Vector3 *other)
{
    x = other->x;
    y = other->y;
    z = other->z;

    return this;
}

std::ostream& operator << (std::ostream& os, const Vector3 & v){
    os <<"(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

