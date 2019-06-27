#include "geometry.h"
#include "vector3.h"
#include "face3.h"
#include <iostream>
#include <array>
#include "face3.h"
#include "buffergeometry.h"

Geometry::Geometry(std::vector<Face3 *> faces,
                   std::vector<std::vector<std::vector<Vector2 *> > > faceVertexUvs,
                   std::vector<Vector3 *> vertices):
    faces{faces},
    faceVertexUvs{faceVertexUvs},
    vertices{vertices}
{

}

Geometry::Geometry(const std::vector<float> &_vertices, const std::vector<float> &_normals, const std::vector<float> &_position)
{
    for(unsigned long int i = 0; i<_vertices.size(); i+=3){
        vertices.push_back(new Vector3(_vertices.at(i), _vertices.at(i+1), _vertices.at(i+2)));
    }

    for(unsigned long int i = 0; i < _vertices.size() / 3; i+=3){
        addFace(i,i+1,i+2,_normals);
    }

    computeFaceNormals();
}

void Geometry::computeFaceNormals()
{
    Vector3* cb = new Vector3();
    Vector3* ab = new Vector3();

    unsigned long int fl = faces.size();

    for (unsigned long int f = 0; f < fl; f++){
        Face3* face = faces.at(f);

        Vector3* vA = vertices.at(face->a);
        Vector3* vB = vertices.at(face->b);
        Vector3* vC = vertices.at(face->c);


        cb->subVectors(vC, vB);
        ab->subVectors(vA, vB);

        cb->cross(ab);

        cb->normalize();
        face->normal->copy(cb);
    }

}

BufferGeometry* Geometry::toBufferGeometry() const
{
    std::vector<float>* _vertices = new std::vector<float>;
    std::vector<float>* _normals = new std::vector<float>;
    for ( unsigned long int i = 0; i < faces.size(); i ++ ) {
        Face3* face = faces.at(i);
        _vertices->push_back(vertices.at(face->a)->x);
        _vertices->push_back(vertices.at(face->a)->y);
        _vertices->push_back(vertices.at(face->a)->z);
        _vertices->push_back(vertices.at(face->b)->x);
        _vertices->push_back(vertices.at(face->b)->y);
        _vertices->push_back(vertices.at(face->b)->z);
        _vertices->push_back(vertices.at(face->c)->x);
        _vertices->push_back(vertices.at(face->c)->y);
        _vertices->push_back(vertices.at(face->c)->z);

        std::vector<Vector3*> vertexNormals = face->vertexNormals;

        if ( vertexNormals.size() == 3 ) {
            _normals->push_back( vertexNormals.at(0)->x);
            _normals->push_back( vertexNormals.at(0)->y);
            _normals->push_back( vertexNormals.at(0)->z);
            _normals->push_back( vertexNormals.at(1)->x);
            _normals->push_back( vertexNormals.at(1)->y);
            _normals->push_back( vertexNormals.at(1)->z);
            _normals->push_back( vertexNormals.at(2)->x);
            _normals->push_back( vertexNormals.at(2)->y);
            _normals->push_back( vertexNormals.at(2)->z);
        } else {
            Vector3* normal = face->normal;
            _normals->push_back(normal->x);
            _normals->push_back(normal->y);
            _normals->push_back(normal->z);

            _normals->push_back(normal->x);
            _normals->push_back(normal->y);
            _normals->push_back(normal->z);

            _normals->push_back(normal->x);
            _normals->push_back(normal->y);
            _normals->push_back(normal->z);
        }
    }

    return new BufferGeometry(_vertices,_normals);
}


void Geometry::addFace(unsigned long a, unsigned long b, unsigned long c, const std::vector<float>& normals)
{

    std::vector<Vector3*> vertexNormals{{
            new Vector3{normals.at(a*3), normals.at(a*3+1), normals.at(a*3+2)},
            new Vector3{normals.at(b*3), normals.at(b*3+1), normals.at(b*3+2)},
            new Vector3{normals.at(c*3), normals.at(c*3+1), normals.at(c*3+2)}
                                        }};



    Face3* face = new Face3(a,b,c, vertexNormals);
    faces.push_back(face);
}
