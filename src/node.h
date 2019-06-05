#ifndef NODE_H
#define NODE_H

#include<vector>

class Polygon;

class Node
{
public:
    Node(const std::vector<Polygon*> _polygons = {});

    bool isConvex(const std::vector<Polygon*> _polygons) const;
    void build(const std::vector<Polygon*> _polygons);
    std::vector<Polygon*> allPolygons() const;
    Node* clone() const;
    Node* invert();
    std::vector<Polygon*> clipPolygons(std::vector<Polygon*> _polygons) const;
    void clipTo(Node* node);

    
private:
    std::vector<Polygon*> polygons;
    Node* front;
    Node* back;
    Polygon* divider;
    
};

#endif // NODE_H
