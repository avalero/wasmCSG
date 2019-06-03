#include <iostream>

#include "vertex.h"
#include "vector2.h"
#include "vector3.h"




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
