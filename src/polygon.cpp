#include "polygon.h"
#include "vertex.h"
#include "vector2.h"
#include "vector3.h"


Polygon::Polygon(std::vector<Vertex *> const & vertices, Vertex *normal, double w):
    vertices{vertices}
{
    if(vertices.size() >= 3){
        calculateProperties();
    }else{
        normal = nullptr;
        w = 0;
    }

}

Polygon* Polygon::calculateProperties()
{
    const Vertex* a = vertices.at(0);
    const Vertex* b = vertices.at(1);
    const Vertex* c = vertices.at(2);

    normal = b->clone()->subtract(a)->cross(c->clone()->subtract(a))->normalize();
    w = normal->clone()->dot(a);

    return this;
}

Polygon *Polygon::clone()
{
    unsigned long i, vertice_count;
    Polygon* polygon = new Polygon();

    for(i=0, vertice_count = vertices.size(); i < vertice_count; i++){
        polygon->vertices.push_back(vertices.at(i)->clone());
    }

    if(polygon->vertices.size() >= 3){
        polygon->calculateProperties();
    }else{
        polygon->normal = nullptr;
        polygon->w = 0;
    }

    return polygon;
}

Polygon *Polygon::flip()
{
    long i;
    std::vector<Vertex*> _vertices;

    normal->multiplyScalar(-1);
    w *= -1;

    for(i = vertices.size() - 1 ; i >= 0 ; i--){
        _vertices.push_back(vertices.at(i));
    }

    vertices = _vertices;

    return this;

}

int Polygon::classifyVertex(const Vertex *vertex)
{
    const double side_value = normal->dot(vertex) - w;

    if (side_value < -EPSILON) return BACK;
    if (side_value > EPSILON) return FRONT;
    return COPLANAR;
}

int Polygon::classifySide(const Polygon *polygon)
{
    unsigned long i;
    Vertex* vertex;
    int classification;
    int num_positive = 0;
    int num_negative = 0;
    unsigned long vertice_count = polygon->vertices.size();

    for(i=0; i < vertice_count; i++){
        vertex = polygon->vertices.at(i);
        classification = classifyVertex(vertex);
        if(classification == FRONT){
            num_positive++;
        }else if(classification == BACK){
            num_negative--;
        }
    }

    if(num_positive > 0 && num_negative ==0)
        return FRONT;
    if (num_positive == 0 && num_negative > 0) {
        return BACK;
    }
    if (num_positive == 0 && num_negative == 0) {
        return COPLANAR;
    } else {
        return SPANNING;
    }
}

void Polygon::splitPolygon(Polygon *polygon, std::vector<Polygon *> &coplanar_front, std::vector<Polygon *> &coplanar_back, std::vector<Polygon *> &front, std::vector<Polygon *> &back)
{
    const int classification = classifySide(polygon);

    if (classification == COPLANAR) {
        (normal->dot(polygon->normal) > 0 ? coplanar_front : coplanar_back).push_back(polygon);
    } else if (classification == FRONT) {
        front.push_back(polygon);
    } else if (classification == BACK) {
        back.push_back(polygon);
    } else {
        unsigned long vertice_count,i,j;
        int ti, tj;
        Vertex *vi, *vj;
        std::vector<Vertex*> f, b;

        double t;
        Vertex* v;

        for ( i = 0, vertice_count = polygon->vertices.size(); i < vertice_count; i++) {
            j = (i + 1) % vertice_count;
            vi = polygon->vertices[i];
            vj = polygon->vertices[j];
            ti = classifyVertex(vi);
            tj = classifyVertex(vj);



            if (ti != BACK) {
                f.push_back(vi);
            }
            if (ti != FRONT) {
                b.push_back(vi);
            }
            if ((ti | tj) == SPANNING) {
                t = (w - normal->dot(vi)) / normal->dot(vj->clone()->subtract(vi));
                v = vi->interpolate(vj, t);
                f.push_back(v);
                b.push_back(v);
            }
        }

        if (f.size() >= 3) {
            /////////
            ///////// REMOVED CALCULATE PROPERTIES REGARDING ORIGINAL BECAUSE THEY ARE CALCULATED IN CONSTRUCTOR
            front.push_back((new Polygon(f)));
        }
        if (b.size() >= 3) {
            back.push_back((new Polygon(b)));
        }
    }
}

