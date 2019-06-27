#include "buffergeometry.h"

BufferGeometry::BufferGeometry(std::vector<float>* vertices, std::vector<float>* normals):
    vertices{vertices},
    normals{normals}
{

}

BufferGeometry::~BufferGeometry()
{
    if(vertices) delete vertices;
    if(normals) delete normals;
}
