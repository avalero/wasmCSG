#ifndef BSPNODE_H
#define BSPNODE_H

#include <vector>

class Triangle;
class Box3;
class Vector3;
class Matrix4;
class Geometry;

Triangle* chooseDividingTriangle(const std::vector<Triangle*> _triangles);

class BSPNode
{
public:
    // static functions
    static Vector3* interpolateVectors(const Vector3* a, const Vector3* b, float t);
    static void splitTriangle(Triangle* triangle,
                              const Triangle* divider,
                              std::vector<Triangle*> frontTriangles,
                              std::vector<Triangle*> backTriangles);

    static std::vector<Vector3*> verticesToTriangles(std::vector<Vector3*>);

public:
    BSPNode(std::vector<Triangle*> _triangles = {});
    ~BSPNode();
    void buildFrom(const std::vector<Triangle *> triangles);
    void invert();

    // Remove all triangles in this BSP tree that are inside the other BSP tree
    void clipTo(BSPNode* tree);

    // Recursively remove all triangles from `triangles` that are inside this BSP tree
    std::vector<Triangle*> clipTriangles(std::vector<Triangle*> _triangles);

    std::vector<Triangle*> getTriangles();

    BSPNode* clone(Matrix4* transform = nullptr);

    Geometry* toGeometry();





private:
    void addTriangles(const std::vector<Triangle*> _triangles);
    // empty triangles vector and free memory
    void deleteTriangles();



protected:
    Triangle* divider;
    BSPNode* front;
    BSPNode* back;
    std::vector<Triangle*> triangles;
    bool isInverted;
    Box3* boundingBox;

};

#endif // BSPNODE_H