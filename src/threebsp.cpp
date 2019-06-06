#include "threebsp.h"

#include "matrix4.h"
#include "geometry.h"
#include "vector3.h"
#include "vector2.h"
#include "polygon.h"
#include "face3.h"
#include "vertex.h"
#include "node.h"

ThreeBSP::ThreeBSP(Geometry* _geometry)
{
    std::array<Vector2*,3> faceVertexUvs;
    Face3* face;
    Polygon* polygon;
    std::vector<Polygon*> polygons;
    Geometry* geometry = _geometry;
    Vector3* vector3;
    Vertex* vertex;
    Vector2* uvs;

    matrix = new Matrix4();

    for(unsigned long i = 0, _length_i = geometry->faces.size(); i < _length_i; i++){
        face = geometry->faces.at(i);
        faceVertexUvs = geometry->faceVertexUvs.at(0).at(i);
        polygon = new Polygon();

        // ASSUME THE FACE IS FACE3, IF NOT WE HAVE TO DEVELOP A FACE4 INSTANCE
        vector3 = geometry->vertices.at(face->a);
        if(faceVertexUvs.size()>0) uvs = new Vector2(faceVertexUvs.at(0)->x, faceVertexUvs.at(0)->y);
        // Line 104 threeCSG.js -> TODO vertexNormals
        vertex = new Vertex(vector3->x, vector3->y, vector3->z, face->vertexNormals.at(0), uvs);
        vertex->applyMatrix4(matrix);
        polygon->vertices.push_back(vertex);
        // END ASSUME FACE IS FACE3, TO BE CHECKED

        polygon->calculateProperties();
        polygons.push_back(polygon);
    }

    tree = new Node{polygons};
}

ThreeBSP::ThreeBSP(Node *tree):
    tree{tree}
{
    matrix = new Matrix4();
}

ThreeBSP *ThreeBSP::subtract(const ThreeBSP *other_tree) const
{
    Node* a = tree->clone();
    Node* b = other_tree->tree->clone();

    a->invert();
    a->clipTo(b);
    b->clipTo(a);
    b->invert();
    a->build(b->allPolygons());
    a->invert();

    ThreeBSP* res = new ThreeBSP{a};
    res->matrix = matrix;
    return res;
}

ThreeBSP *ThreeBSP::comp_union(const ThreeBSP *other_tree) const
{
    Node* a = tree->clone();
    Node* b = other_tree->tree->clone();

    a->clipTo(b);
    b->clipTo(a);
    b->invert();
    b->clipTo(a);
    b->invert();
    a->build(b->allPolygons());

    ThreeBSP* res = new ThreeBSP{a};
    res->matrix = matrix;
    return res;
}

ThreeBSP *ThreeBSP::intersect(const ThreeBSP *other_tree) const
{
    Node* a = tree->clone();
    Node* b = other_tree->tree->clone();

    a->invert();
    b->clipTo(a);
    b->invert();
    a->clipTo(b);
    b->clipTo(a);
    a->build(b->allPolygons());
    a->invert();

    ThreeBSP* res = new ThreeBSP{a};
    res->matrix = matrix;
    return res;
}
