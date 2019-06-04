#ifndef MATRIX4_H
#define MATRIX4_H

#include <array>

class Matrix4
{
public:
    Matrix4();

    std::array<double, 16>* elements;
};

#endif // MATRIX4_H
