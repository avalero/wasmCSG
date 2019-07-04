#include "triangle.h"

#include "vector3.h"
#include "math.h"


Triangle::Triangle(const Vector3 *a, const Vector3 *b, const Vector3 *c):
    a{a->clone()},
    b{b->clone()},
    c{c->clone()},
    normal{new Vector3()},
    w{0}
{
    computeNormal();

}

void Triangle::computeNormal()
{
    Vector3* temp{c};
    temp->sub(a);
    normal->copy(b)->sub(a)->cross(temp)->normalize();
    w = normal->dot(a);
}

SIDE_CLASSIFICATION Triangle::classifyPoint(const Vector3* point) const
{
    float side = normal->dot(point) - w;
    if(fabs(side) < EPSILON) return CLASSIFY_COPLANAR;
    if(side > 0) return CLASSIFY_FRONT;
    return CLASSIFY_BACK;
}

SIDE_CLASSIFICATION Triangle::classifySide(const Triangle *triangle) const
{
    SIDE_CLASSIFICATION side = CLASSIFY_COPLANAR;
    side = SIDE_CLASSIFICATION(side | classifyPoint(triangle->a));
    side = SIDE_CLASSIFICATION(side | classifyPoint(triangle->b));
    side = SIDE_CLASSIFICATION(side | classifyPoint(triangle->c));

    return side;
}

void Triangle::invert()
{
    Vector3* aux_a = a;
    Vector3* aux_c = c;

    a = aux_c;
    c = aux_a;
    normal->multiplyScalar(-1);
    w *= -1;
}

Triangle *Triangle::clone() const
{
    return new Triangle(a,b,c);
}
