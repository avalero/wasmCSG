#include "face3.h"
#include "vector3.h"


Face3::Face3(unsigned long a, unsigned long b, unsigned long c, Vector3 *normal):
    a{a},
    b{b},
    c{c},
    normal{normal}
{
    if(!normal) normal = new Vector3();
}

Face3::Face3(unsigned long a, unsigned long b, unsigned long c, std::vector<Vector3 *> vertexNormals):
    a{a},
    b{b},
    c{c},
    vertexNormals{vertexNormals}
{
    normal = new Vector3();
}

Face3::~Face3()
{
    delete normal; normal = nullptr;
    for(auto v: vertexNormals){
        delete v; v = nullptr;
    }
    vertexNormals.clear();
}

Face3 *Face3::clone() const
{
    return new Face3(a,b,c,normal->clone());
}

Face3 *Face3::copy(const Face3 *source)
{
    a = source->a;
    b = source->b;
    c = source->c;

    //delete normal to set new one
    delete normal;
    normal = source->normal->clone();

    return this;
}

std::ostream &operator <<(std::ostream &os, const Face3 &f)
{
    os << "a: " << f.a << ", b: " << f.b << ", c: " << f.c << " - ";
    os << " normal: " << *(f.normal);
    return os;
}
