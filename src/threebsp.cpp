#include "threebsp.h"

#include "matrix4.h"
#include "geometry.h"
#include "vector3.h"
#include "vector2.h"
#include "polygon.h"
#include "face3.h"
#include "vertex.h"
#include "node.h"

#include <map>
#include <sstream>
#include <iostream>

ThreeBSP::ThreeBSP(Geometry* _geometry)
{
    std::vector<Polygon*> polygons;
    Geometry* geometry = _geometry;
    Vector3* vector3;
    Vertex* vertex;


    matrix = new Matrix4();

    unsigned long int _length_i = geometry->faces.size();

    for(unsigned long i = 0; i < _length_i; i++){

        Face3* face = geometry->faces.at(i);

        Polygon* polygon = new Polygon();

        vector3 = geometry->vertices.at(face->a);
        vertex = new Vertex(vector3->x, vector3->y, vector3->z, face->vertexNormals.at(0));
        vertex->applyMatrix4(matrix);
        polygon->vertices.push_back(vertex);


        vector3 = geometry->vertices.at(face->b);
        vertex = new Vertex(vector3->x, vector3->y, vector3->z, face->vertexNormals.at(1));
        vertex->applyMatrix4(matrix);
        polygon->vertices.push_back(vertex);

        vector3 = geometry->vertices.at(face->c);
        vertex = new Vertex(vector3->x, vector3->y, vector3->z, face->vertexNormals.at(2));
        vertex->applyMatrix4(matrix);
        polygon->vertices.push_back(vertex);

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

Geometry *ThreeBSP::toGeometry() const
{

    Matrix4* _matrix = (new Matrix4())->getInverse(matrix);
    Geometry* _geometry = new Geometry();

    std::vector<Polygon*> _polygons = tree->allPolygons();

    Polygon* _polygon;
    unsigned long vertex_idx_a;
    unsigned long vertex_idx_b;
    unsigned long vertex_idx_c;


    Face3* _face;
    std::map<std::string, unsigned long int> vertice_dict;


    unsigned long polygon_count = _polygons.size();

    for(unsigned long i=0; i < polygon_count; i++){
        _polygon = _polygons.at(i);
        unsigned long polygon_vertice_count = _polygon->vertices.size();
        for(unsigned long int j=2; j < polygon_vertice_count; j++){
            std::vector<Vector2*> verticesUvs;
            Vertex* _vertex = _polygon->vertices.at(0);
            verticesUvs.push_back(new Vector2(_vertex->uv->x, _vertex->uv->y));
            Vector3* _vector3 = new Vector3(_vertex->x, _vertex->y, _vertex->z);
            _vector3->applyMatrix4(_matrix);
            std::ostringstream stream;
            stream << _vector3->x <<","<< _vector3->y <<","<< _vector3->z;
            std::string key =  stream.str();
            if ( vertice_dict.find(key) != vertice_dict.end() ) {
                vertex_idx_a = vertice_dict.at(key);
            }else{
                _geometry->vertices.push_back(_vector3);
                vertex_idx_a = _geometry->vertices.size() - 1 ;
                vertice_dict.insert(std::pair<std::string, unsigned long>(key, vertex_idx_a));
            }



            _vertex = _polygon->vertices.at(j-1);
            verticesUvs.push_back(new Vector2(_vertex->uv->x, _vertex->uv->y));
            _vector3 = new Vector3(_vertex->x, _vertex->y, _vertex->z);
            _vector3->applyMatrix4(_matrix);


            stream.str(std::string());
            stream << _vector3->x <<","<< _vector3->y <<","<< _vector3->z;
            key =  stream.str();


            if ( vertice_dict.find(key) != vertice_dict.end() ) {
                vertex_idx_b = vertice_dict.at(key);
            }else{
                _geometry->vertices.push_back(_vector3);
                vertex_idx_b = _geometry->vertices.size() - 1 ;
                vertice_dict.insert(std::pair<std::string, unsigned long>(key, vertex_idx_b));
            }


            _vertex = _polygon->vertices.at(j);
            verticesUvs.push_back(new Vector2(_vertex->uv->x, _vertex->uv->y));
            _vector3 = new Vector3(_vertex->x, _vertex->y, _vertex->z);
            _vector3->applyMatrix4(_matrix);

            stream.str(std::string());
            stream << _vector3->x <<","<< _vector3->y <<","<< _vector3->z;
            key =  stream.str();


            if ( vertice_dict.find(key) != vertice_dict.end() ) {
                vertex_idx_c = vertice_dict.at(key);
            }else{
                _geometry->vertices.push_back(_vector3);
                vertex_idx_c = _geometry->vertices.size() - 1 ;
                vertice_dict.insert(std::pair<std::string, unsigned long>(key, vertex_idx_c));
            }


            _face = new Face3(vertex_idx_a, vertex_idx_b, vertex_idx_c,
                              new Vector3(_polygon->normal->x, _polygon->normal->y,_polygon->normal->z ));

            _geometry->faces.push_back(_face);

            if(_geometry->faceVertexUvs.size() == 0) _geometry->faceVertexUvs.push_back({verticesUvs});
            else _geometry->faceVertexUvs.at(0).push_back(verticesUvs);

        }

    }



    return _geometry;
}
