#ifndef BUFFERGEOMETRY_H
#define BUFFERGEOMETRY_H

#include <vector>


class BufferGeometry
{
public:
    BufferGeometry(std::vector<float>* vertices, std::vector<float>* normals);
    ~BufferGeometry();
    std::vector<float>* vertices;
    std::vector<float>* normals;
};

#endif // BUFFERGEOMETRY_H
