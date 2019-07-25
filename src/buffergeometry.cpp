#include "buffergeometry.h"

BufferGeometry::BufferGeometry(std::vector<float>* vertices, std::vector<float>* normals):
    vertices{vertices},
    normals{normals}
{

}

BufferGeometry::~BufferGeometry()
{
    delete vertices; vertices = nullptr;
    delete normals; normals = nullptr;
}
