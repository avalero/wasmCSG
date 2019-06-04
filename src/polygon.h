#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

class Vertex;
class Vector3;
class Vector2;

class Polygon
{
public:
    Polygon(const std::vector<Vertex *> &vertices = {}, Vertex* normal = nullptr, double w = 0);
    Polygon *calculateProperties();
    Polygon* clone();
    Polygon* flip();
    int classifyVertex(const Vertex* vertex);
    int classifySide(const Polygon* polygon);
    void splitPolygon(Polygon *polygon,
                     std::vector<Polygon*> &coplanar_front,
                     std::vector<Polygon*> &coplanar_back,
                     std::vector<Polygon*> & front,
                     std::vector<Polygon*> & back
                     );

private:
    std::vector<Vertex*> vertices;
    Vertex* normal;
    double w;

    const double EPSILON = 1e-5;
    const int COPLANAR = 0;
    const int FRONT = 1;
    const int BACK = 2;
    const int SPANNING = 3;
};

#endif
