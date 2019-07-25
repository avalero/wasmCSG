#ifndef BOX3_H
#define BOX3_H

#include <ostream>

class Vector3;

class Box3
{
    friend std::ostream & operator << (std::ostream & os, Box3 const & box);

public:
    Box3(Vector3* min, Vector3* max);
    Box3();
    ~Box3();


    bool intersectsBox(const Box3* box) const;
    Vector3* min;
    Vector3* max;
};

std::ostream & operator << (std::ostream & os, Box3 const & box);


#endif // BOX3_H
