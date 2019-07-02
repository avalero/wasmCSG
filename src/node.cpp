#include "node.h"
#include "polygon.h"


#include "constants.h"

Node::Node(const std::vector<Polygon *> _polygons)
{

    std::vector<Polygon*> _front;
    std::vector<Polygon*> _back;
    
    front = back = nullptr;
    
    if(_polygons.size() == 0) return;
    
    divider = _polygons.at(0)->clone();

    unsigned long int polygon_count = _polygons.size();
    for(unsigned long int i=0; i < polygon_count; i++){
        divider->splitPolygon(
                    _polygons.at(i),
                    polygons,
                    polygons,
                    _front,
                    _back);
    }

    if(_front.size() > 0){
        front = new Node{_front};
    }

    if(_back.size() > 0){
        back = new Node{_back};
    }  
}

bool Node::isConvex(const std::vector<Polygon *> _polygons) const
{
    unsigned long i,j;
    for(i=0; i < _polygons.size(); i++){
        for(j=0; j < _polygons.size(); j++){
            if( i != j && _polygons.at(i)->classifySide(_polygons.at(j)) != BACK){
                return false;
            }
        }
    }

    return true;
}

void Node::build(const std::vector<Polygon *> _polygons)
{
    unsigned long i, polygon_count;
    std::vector<Polygon*> _front;
    std::vector<Polygon*> _back;



    if(!divider){
        divider = _polygons.at(0)->clone();
    }

    for(i=0, polygon_count = _polygons.size(); i < polygon_count; i++){
        divider->splitPolygon(
                    _polygons.at(i),
                    polygons,
                    polygons,
                    _front,
                    _back);
    }

    if(_front.size() > 0){
        if(!front) front = new Node{};
        front->build(_front);
    }

    if(_back.size() > 0){
        if(!back) back = new Node{};
        back->build(_back);
    }

}

std::vector<Polygon *> Node::allPolygons() const
{
    std::vector<Polygon *> _polygons = polygons;
    if(front){
        std::vector<Polygon *> frontAll = front->allPolygons();
        _polygons.insert(_polygons.end(), frontAll.begin(), frontAll.end());
    }

    if(back){
       std::vector<Polygon *> backAll = back->allPolygons();
       _polygons.insert(_polygons.end(), backAll.begin(), backAll.end());
    }

    return _polygons;

}

Node *Node::clone() const
{
    Node* node = new Node();
    node->divider = divider->clone();
    for(unsigned long i = 0 ; i< polygons.size(); i++){
        node->polygons.push_back(polygons.at(i)->clone());
    }

    node->front = (front) ? front->clone(): nullptr;
    node->back = (back) ? back->clone() : nullptr;

    return node;
}

Node *Node::invert()
{
    unsigned long i, polygon_count;
    Node* temp;

    for(i=0, polygon_count = polygons.size(); i< polygon_count; i++){
        polygons.at(i)->flip();
    }

    divider->flip();

    if(front) front->invert();
    if(back) back->invert();

    temp = front;
    front = back;
    back = temp;

    return this;
}

std::vector<Polygon *> Node::clipPolygons(std::vector<Polygon *> _polygons) const
{
    unsigned long i, polygon_count;
    std::vector<Polygon*> _front;
    std::vector<Polygon*> _back;

    if(!divider){
        return polygons;
    }

    for(i = 0, polygon_count = polygons.size(); i < polygon_count; i++){
        divider->splitPolygon(_polygons.at(i), _front, _back, _front, _back);
    }

    if(front) _front = front->clipPolygons(_front);
    if(back) _back = back->clipPolygons(_back);

    _front.insert(_front.end(), _back.begin(), _back.end());
    return _front;
}

void Node::clipTo(Node *node)
{
    polygons = node->clipPolygons(polygons);
    if(front) front->clipTo(node);
    if(back) back->clipTo(node);
}
