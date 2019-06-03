#include <iostream>
#include <math.h>
#include <array>

#include "vertex.h"
#include "vector2.h"
#include "vector3.h"
#include "matrix4.h"




Vertex::Vertex(float x, float y, float z, Vector3* normal, Vector2* uv) :
    x{x},
    y{y},
    z{z},
    normal{normal},
    uv{uv}
{
    if(!normal) normal = new Vector3();
    if(!uv) uv = new Vector2();
    std::cout << "New Vertex: " << x << ", " << y << std::endl;
}

Vertex::Vertex(Vertex *v): Vertex{v->x, v->y, v->z, v->normal->clone(),v->uv->clone()}
{
    std::cout << "Vertex cloned" << std::endl;
}

Vertex *Vertex::clone()
{
    return new Vertex(this);
}

Vertex *Vertex::add(Vertex *other)
{
    x += other->x;
    y += other->y;
    z += other->z;

    return this;
}

Vertex *Vertex::subtract(Vertex *other)
{
    x -= other->x;
    y -= other->y;
    z -= other->z;

    return this;

}

Vertex *Vertex::multiplyScalar(float number)
{
    x *= number;
    y *= number;
    z *= number;

    return this;
}

Vertex *Vertex::cross(Vertex *other)
{
    const float _x = x;
    const float _y = y;
    const float _z = z;

    x = _y * other->z - _z * other->y;
    y = _z * other->x - _x * other->z;
    z = _x * other->y - _y * other->x;

    return this;
}

Vertex *Vertex::normalize()
{
    const float length = sqrt(x*x + y*y + z*z);
    x /= length;
    y /= length;
    z /= length;

    return this;
}

float Vertex::dot(Vertex *other)
{
    return x*other->x + y*other->y + z*other->z;
}

Vertex *Vertex::lerp(Vertex *a, float t)
{
    this->add(a->clone()->subtract(this)->multiplyScalar(t));
    this->normal->add(a->normal->clone()->sub(this->normal)->multiplyScalar(t));
    this->uv->add(a->uv->clone()->sub(this->uv)->multiplyScalar(t));

    return this;
}

Vertex *Vertex::interpolate(Vertex *other, float t)
{
    return this->clone()->lerp(other,t);
}

Vertex *Vertex::applyMatrix4(Matrix4 *m)
{
    const float _x = this->x;
    const float _y = this->y;
    const float _z = this->z;

    const std::array<float,16>* e = m->elements;

    this->x = e->at(0) * _x + e->at(4) * _y + e->at(8) * _z + e->at(12);
    this->y = e->at(1) * _x + e->at(5) * _y + e->at(9) * _z + e->at(13);
    this->z = e->at(2) * _x + e->at(6) * _y + e->at(10) *_z + e->at(14);

    return this;
}

std::ostream &operator <<(std::ostream &os, Vertex * const v)
{
    os << *v;
    // os << v->x << ", " << v->y << ", " << v->z;
    return os;
}

std::ostream &operator <<(std::ostream &os, const Vertex &v)
{
    os << v.x << ", " << v.y << ", " << v.z;
    return os;
}
