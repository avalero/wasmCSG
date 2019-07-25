#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <ostream>
#include <vector>

#include "constants.h"

class Vector3;

class Triangle
{
    friend class BSPNode;
    friend std::ostream & operator << (std::ostream & os, Triangle const & t);
public:
    Triangle(const Vector3 *a, const Vector3 *b, const Vector3 *c);
    ~Triangle();


protected:
    Vector3* a;
    Vector3* b;
    Vector3* c;
    Vector3* normal;
    float w;

public:
    void computeNormal();
    SIDE_CLASSIFICATION classifyPoint(const Vector3* point) const;
    SIDE_CLASSIFICATION classifySide(const Triangle* triangle) const;
    void invert();
    Triangle* clone() const;

};

std::ostream & operator << (std::ostream & os, Triangle const & t);
std::ostream& operator << (std::ostream& os, std::vector<Triangle*> v);

#endif // TRIANGLE_H
