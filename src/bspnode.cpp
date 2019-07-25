#include "bspnode.h"

#include "utils.h"
#include "constants.h"
#include "triangle.h"
#include "box3.h"
#include "vector3.h"
#include "geometry.h"
#include "face3.h"

#include <array>
#include <algorithm>
#include <iostream>


Vector3 *BSPNode::interpolateVectors(const Vector3 *a, const Vector3 *b, float t)
{
    return a->clone()->lerp(b,t);
}

void BSPNode::splitTriangle(Triangle *triangle, const Triangle *divider, std::vector<Triangle *> & frontTriangles, std::vector<Triangle *> & backTriangles)
{

    std::vector<Vector3*> vertices = {triangle->a, triangle->b, triangle->c};


    std::vector<Vector3*> frontVertices;
    std::vector<Vector3*> backVertices;

    for(unsigned short i = 0 ; i < 3 ; i++){
        unsigned short j = (i + 1) % 3;
        auto vi = vertices.at(i);
        auto vj = vertices.at(j);
        auto ti = divider->classifyPoint(vi);
        auto tj = divider->classifyPoint(vj);

        if(ti != CLASSIFY_BACK) frontVertices.push_back(vi);
        if(ti != CLASSIFY_FRONT) backVertices.push_back(vi);
        if(( ti | tj) == CLASSIFY_SPANNING){
            auto vjClone = vj->clone();
            float t = float(divider->w - divider->normal->dot(vi))/
                    divider->normal->dot(vjClone->sub(vi));

            delete vjClone; vjClone = nullptr;

            Vector3* v = BSPNode::interpolateVectors(vi, vj, t);
            frontVertices.push_back(v);
            backVertices.push_back(v);
        }
    }

    if(frontVertices.size() > 3){
        auto aux = BSPNode::verticesToTriangles(frontVertices);
        frontTriangles.insert(frontTriangles.end(), aux.begin(), aux.end());
    }

    if(backVertices.size() > 3){
        auto aux = BSPNode::verticesToTriangles(backVertices);
        backTriangles.insert(backTriangles.end(), aux.begin(), aux.end());
    }
}

std::vector<Triangle*> BSPNode::verticesToTriangles(const std::vector<Vector3 *> & vertices)
{
    std::vector<Triangle*> triangles;
    for(unsigned int i = 2; i < vertices.size(); i++){
        auto a = vertices.at(0);
        auto b = vertices.at(i-1);
        auto c = vertices.at(i);
        auto triangle = new Triangle(a,b,c);
        triangles.push_back(triangle);
    }
    return triangles;
}

BSPNode::BSPNode(std::vector<Triangle *> _triangles):
    divider{nullptr},
    front{nullptr},
    back{nullptr},
    isInverted{false},
    boundingBox{new Box3()}
{
    if(_triangles.size() > 0) buildFrom(_triangles);
}

BSPNode::~BSPNode()
{
    delete divider; divider = nullptr;
    delete front; front = nullptr;
    delete back; back = nullptr;
    delete boundingBox; boundingBox = nullptr;
    deleteTriangles();
}

void BSPNode::buildFrom(const std::vector<Triangle *> _triangles)
{

    if(!divider){
        Triangle* bestDivider = chooseDividingTriangle(_triangles);
        if(!bestDivider){
            divider = _triangles.at(0)->clone();
            triangles = _triangles;

        }else{
            divider = bestDivider->clone();
            addTrianglesIterative(_triangles);

        }
    }else{
        addTrianglesIterative(_triangles);
    }
}

void BSPNode::invert()
{
    isInverted = !isInverted;
    if(divider) divider->invert();
    if(front) front->invert();
    if(back) back->invert();

    auto temp = front;
    front = back;
    back = temp;

    for(auto t: triangles){
        t->invert();
    }
}

/**
 * Remove all triangles in this BSP tree that are inside the other BSP tree
 */
void BSPNode::clipTo(BSPNode *tree)
{
    if(
            ! tree->isInverted &&
            ! isInverted &&
            ! boundingBox->intersectsBox(tree->boundingBox)
            )
    {
        return;
    }

    triangles = tree->clipTriangles(triangles);
    if(front) front->clipTo(tree);
    if(back) back->clipTo(tree);
}

std::vector<Triangle *> BSPNode::clipTriangles(std::vector<Triangle *> _triangles)
{
    if(divider) return _triangles;

    std::vector<Triangle*> frontTriangles;
    std::vector<Triangle*> backTriangles;

    for(auto triangle: _triangles){
        auto side = divider->classifySide(triangle);
        switch(side){
        case CLASSIFY_COPLANAR:
        {
            float dot = divider->normal->dot(triangle->normal);
            if(dot>0){
                frontTriangles.push_back(triangle);
            }else{
                backTriangles.push_back(triangle);
            }
            break;
        }
        case CLASSIFY_FRONT:
            frontTriangles.push_back(triangle);
            break;
        case CLASSIFY_BACK:
            backTriangles.push_back(triangle);
            break;
        case CLASSIFY_SPANNING:
            BSPNode::splitTriangle(triangle, divider, frontTriangles, backTriangles);
        }
    }

    if(this->front) frontTriangles = front->clipTriangles(frontTriangles);
    if(this->back) backTriangles = back->clipTriangles(backTriangles);
    else backTriangles.clear();

    frontTriangles.insert(frontTriangles.end(), backTriangles.begin(), backTriangles.end());
    return frontTriangles;
}

std::vector<Triangle *> BSPNode::getTriangles() const
{
    std::vector<Triangle*> _triangles = triangles;
    if(front){
        std::vector<Triangle*> frontTr = front->getTriangles();
        _triangles.insert(_triangles.end(), frontTr.begin(), frontTr.end());
    }
    if(back){
        std::vector<Triangle*> backTr = back->getTriangles();
        _triangles.insert(_triangles.end(), backTr.begin(), backTr.end());
    }

    return _triangles;
}

BSPNode *BSPNode::clone(Matrix4 *transform) const
{

    auto _clone = new BSPNode();
    _clone->isInverted = isInverted;

    _clone->boundingBox->min->copy(boundingBox->min);
    _clone->boundingBox->max->copy(boundingBox->max);

    if(transform){
        _clone->boundingBox->min->applyMatrix4(transform);
        _clone->boundingBox->max->applyMatrix4(transform);
    }

    if(divider){
        _clone->divider = divider->clone();
        if(transform){
            _clone->divider->a->applyMatrix4(transform);
            _clone->divider->b->applyMatrix4(transform);
            _clone->divider->c->applyMatrix4(transform);
        }
    }

    if(front) _clone->front = front->clone();
    if(back) _clone->back = back->clone();

    std::vector<Triangle*> clonedTriangles;
    for(auto triangle: triangles){
        auto clonedTriangle = triangle->clone();
        if(transform){
            clonedTriangle->a->applyMatrix4(transform);
            clonedTriangle->b->applyMatrix4(transform);
            clonedTriangle->c->applyMatrix4(transform);
            clonedTriangle->computeNormal();
        }
        clonedTriangles.push_back(clonedTriangle);
    }

    _clone->triangles = clonedTriangles;

    return _clone;
}

Geometry *BSPNode::toGeometry() const
{
    Geometry* geometry = new Geometry();

    std::vector<Triangle*> triangles = getTriangles();
    for(unsigned long int i = 0; i < triangles.size(); i++){
        Triangle* triangle = triangles.at(i);
        auto vertexIndex = geometry->vertices.size();
        geometry->vertices.push_back(triangle->a->clone());
        geometry->vertices.push_back(triangle->b->clone());
        geometry->vertices.push_back(triangle->c->clone());
        Face3* face = new Face3(vertexIndex, vertexIndex +1, vertexIndex +2, triangle->normal->clone());
        geometry->faces.push_back(face);
    }
    return geometry;
}

void BSPNode::addTriangles(const std::vector<Triangle *> _triangles,
                           std::vector<Triangle*> & frontTriangles,
                           std::vector<Triangle*> & backTriangles )
{
    frontTriangles.clear();
    backTriangles.clear();

    if(!divider) {
        Triangle * bestTriangle = chooseDividingTriangle(_triangles);
        divider = bestTriangle ? bestTriangle->clone() : _triangles.at(0);
    }
    for(auto triangle: _triangles){
        std::array<float, 4> aux_x_min{ {boundingBox->min->x, triangle->a->x, triangle->b->x, triangle->c->x} };
        std::array<float, 4> aux_y_min{ {boundingBox->min->y, triangle->a->y, triangle->b->y, triangle->c->y} };
        std::array<float, 4> aux_z_min{ {boundingBox->min->z, triangle->a->z, triangle->b->z, triangle->c->z} };

        auto min_x = std::min_element(aux_x_min.begin(), aux_x_min.end());
        auto min_y = std::min_element(aux_y_min.begin(), aux_y_min.end());
        auto min_z = std::min_element(aux_z_min.begin(), aux_z_min.end());

        boundingBox->min->set(
                    *min_x,
                    *min_y,
                    *min_z
                    );

        std::array<float, 4> aux_x_max{ {boundingBox->max->x, triangle->a->x, triangle->b->x, triangle->c->x}};
        std::array<float, 4> aux_y_max{ {boundingBox->max->y, triangle->a->y, triangle->b->y, triangle->c->y}};
        std::array<float, 4> aux_z_max{ {boundingBox->max->z, triangle->a->z, triangle->b->z, triangle->c->z}};

        auto max_x = std::max_element(aux_x_max.begin(), aux_x_max.end());
        auto max_y = std::max_element(aux_y_max.begin(), aux_y_max.end());
        auto max_z = std::max_element(aux_z_max.begin(), aux_z_max.end());

        boundingBox->max->set(
                    *max_x,
                    *max_y,
                    *max_z
                    );



        SIDE_CLASSIFICATION side = divider->classifySide(triangle);

        switch(side){
        case CLASSIFY_COPLANAR:
            triangles.push_back(triangle);
            break;
        case CLASSIFY_FRONT:
            frontTriangles.push_back(triangle);
            break;
        case CLASSIFY_BACK:
            backTriangles.push_back(triangle);
            break;
        default:
            BSPNode::splitTriangle(triangle, divider, frontTriangles, backTriangles);

        }
    }
}

void BSPNode::addTrianglesIterative(const std::vector<Triangle *> &triangles)
{
    std::vector<HeapItem*> heap;
    std::vector<Triangle*> frontTriangles;
    std::vector<Triangle*> backTriangles;

    addTriangles(triangles, frontTriangles, backTriangles);


    if(backTriangles.size() > 0){
        std::cout << "back" << std::endl;
        if(!back) back = new BSPNode();
        heap.push_back(new HeapItem{backTriangles, back});
    }


    if(frontTriangles.size() > 0){
        std::cout << "front" << std::endl;
        if(!front) front = new BSPNode();
        heap.push_back(new HeapItem{frontTriangles, front});
    }


    int i = 0;
    while(heap.size() > 0){
        std::cout << ++i << std::endl;
        std::vector<Triangle*> frontTriangles;
        std::vector<Triangle*> backTriangles;

        HeapItem* item = heap.back();
        heap.pop_back();

        BSPNode* node = item->node;
        std::vector<Triangle*> triangles = item->triangles;

        node->addTriangles(triangles, frontTriangles, backTriangles);

        if (backTriangles.size() > 0) {
            std::cout << "back" << std::endl;

            if (!(node->back)) node->back = new BSPNode();
            heap.push_back(new HeapItem{backTriangles,node->back});
        }

        if (frontTriangles.size() > 0) {
            std::cout << "front" << std::endl;

            if (!(node->front)) node->front = new BSPNode();
            heap.push_back(new HeapItem{frontTriangles,node->front});
        }

        delete item;
    }
}

void BSPNode::deleteTriangles()
{
    for(auto t: triangles){
        delete t; t=nullptr;
    }
    triangles.clear();
}

Triangle *chooseDividingTriangle(const std::vector<Triangle *> _triangles)
{
    if(_triangles.size() == 0) return nullptr;
    return _triangles.at(_triangles.size()/2);

    // TODO!!!!
}
