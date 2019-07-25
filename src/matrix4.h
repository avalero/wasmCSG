#ifndef MATRIX4_H
#define MATRIX4_H

#include <array>

class Matrix4
{
public:
    Matrix4();
    ~Matrix4();

    Matrix4* getInverse(Matrix4* m);
    std::array<float, 16>* elements;
};

#endif // MATRIX4_H
