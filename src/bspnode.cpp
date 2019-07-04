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

/**
 * Algorithm adapted from Binary Space Partioning Trees and Polygon Removal in Real Time 3D Rendering
 * Samuel Ranta-Eskola, 2001
 */


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
    delete divider;
    delete front;
    delete back;
    delete boundingBox;
    deleteTriangles();
}

void BSPNode::buildFrom(const std::vector<Triangle *> _triangles)
{
    if(!divider){
        Triangle* bestDivider = chooseDividingTriangle(_triangles);
        if(!bestDivider){
            divider = triangles.at(0)->clone();
        }else{
            divider = bestDivider->clone();
            deleteTriangles();
            addTriangles(_triangles);
        }
    }else{
        addTriangles(_triangles);
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
    auto _triangles = triangles;
    if(front) _triangles.insert(_triangles.end(), front->getTriangles().begin(), front->getTriangles().end());
    if(back) _triangles.insert(_triangles.end(), back->getTriangles().begin(), back->getTriangles().end());

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

    auto triangles = getTriangles();
    for(auto triangle: triangles){
        auto vertexIndex = geometry->vertices.size();
        geometry->vertices.push_back(triangle->a);
        geometry->vertices.push_back(triangle->b);
        geometry->vertices.push_back(triangle->c);

        auto face = new Face3(vertexIndex, vertexIndex +1, vertexIndex +2, triangle->normal);
        geometry->faces.push_back(face);
    }
    return geometry;
}

void BSPNode::addTriangles(const std::vector<Triangle *> _triangles)
{
    std::vector<Triangle*> frontTriangles;
    std::vector<Triangle*> backTriangles;



    for(auto triangle: _triangles){
        std::array<float, 4> aux1{ {boundingBox->min->x, triangle->a->x, triangle->b->x, triangle->c->x} };
        std::array<float, 4> aux2{ {boundingBox->min->y, triangle->a->y, triangle->b->y, triangle->c->y} };
        std::array<float, 4> aux3{ {boundingBox->min->z, triangle->a->z, triangle->b->z, triangle->c->z} };

        auto minmax_x = std::minmax_element(aux1.begin(), aux1.end());
        auto minmax_y = std::minmax_element(aux2.begin(), aux2.end());
        auto minmax_z = std::minmax_element(aux3.begin(), aux3.end());

        boundingBox->min->set(
                    *minmax_x.first,
                    *minmax_y.first,
                    *minmax_z.first
                    );
        boundingBox->max->set(
                    *minmax_x.second,
                    *minmax_y.second,
                    *minmax_z.second
                    );

        auto side = divider->classifySide(triangle);
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

        if(frontTriangles.size() > 0){
            if(!front) front = new BSPNode(frontTriangles);
            else front->addTriangles(frontTriangles);
        }

        if(backTriangles.size() > 0){
            if(!back) back = new BSPNode(backTriangles);
            else back->addTriangles(backTriangles);
        }


    }
}

void BSPNode::deleteTriangles()
{
    for(auto t: triangles){
        delete t;
    }
    triangles.clear();
}

Triangle *chooseDividingTriangle(const std::vector<Triangle *> _triangles)
{
    if(_triangles.size() == 0) return nullptr;
    return _triangles.at(0);

    // TODO!!!!
}
