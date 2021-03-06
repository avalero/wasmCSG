#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

class Vertex;
class Vector3;
class Vector2;

class Polygon
{
    friend class ThreeBSP;
public:
    Polygon(const std::vector<Vertex *> &vertices = {}, Vertex* normal = nullptr, float w = 0);
    Polygon *calculateProperties();
    Polygon* clone() const;
    Polygon* flip();
    int classifyVertex(const Vertex* vertex);
    int classifySide(const Polygon* polygon);
    void splitPolygon(Polygon *polygon,
                     std::vector<Polygon*> &coplanar_front,
                     std::vector<Polygon*> &coplanar_back,
                     std::vector<Polygon*> & front,
                     std::vector<Polygon*> & back
                     );

protected:
    std::vector<Vertex*> vertices;
    Vertex* normal;
    float w;
};

#endif
