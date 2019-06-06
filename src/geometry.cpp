#include "geometry.h"

Geometry::Geometry(std::vector<Face3 *> faces,
                   std::vector<std::vector<std::array<Vector2 *, 3> > > faceVertexUvs,
                   std::vector<Vector3 *> vertices):
    faces{faces},
    faceVertexUvs{faceVertexUvs},
    vertices{vertices}
{

}
