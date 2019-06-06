#ifndef THREEBSP_H
#define THREEBSP_H

#include <vector>
#include <array>

class Node;
class Matrix4;
class Vector2;
class Face3;
class Geometry;

class ThreeBSP
{
public:
    ThreeBSP(Geometry* _geometry);
    ThreeBSP(Node* tree);
    ThreeBSP *subtract(const ThreeBSP* other_tree) const;
    ThreeBSP *comp_union(const ThreeBSP* other_tree) const;
    ThreeBSP *intersect(const ThreeBSP* other_tree) const;

private:
    Node* tree;
    Matrix4* matrix;

};

#endif // THREEBSP_H
