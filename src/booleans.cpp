#include "booleans.h"
#include "bspnode.h"

#include <iostream>

BSPNode* intersect(const BSPNode* a, const BSPNode* b){
    auto a2 = a->clone();
    auto b2 = b->clone();

    a2->invert();
    b2->clipTo(a2);
    b2->invert();
    a2->clipTo(b2);
    b2->clipTo(a2);
    a2->invert();
    b2->invert();
    a2->buildFrom(b2->getTriangles());

    return a2;
}

BSPNode *add(const BSPNode *a, const BSPNode *b)
{
    auto a2 = a->clone();
    auto b2 = b->clone();
    a2->clipTo(b2);
    b2->clipTo(a2);
    b2->invert();
    b2->clipTo(a2);
    b2->invert();
    a2->buildFrom(b2->getTriangles());
    return a2;

}

BSPNode *subtract(const BSPNode *a, const BSPNode *b)
{
    auto a2 = a->clone();
    auto b2 = b->clone();
    a2->invert();
    a2->clipTo(b2);
    b2->clipTo(a2);
    b2->invert();
    b2->clipTo(a2);
    a2->invert();
    a2->buildFrom(b2->getTriangles());
    return a2;
}

BSPNode *intersect(std::vector<BSPNode *> items)
{
    if(items.size()==0){
        std::cout << "No items to perform action";
        // throw std::runtime_error{"No items to perform action"};
    }

    auto res = items.at(0);
    for(unsigned long int i = 1; i < items.size(); i++){
        res = intersect(res, items.at(i));
    }

    return res;

}

BSPNode *add(std::vector<BSPNode *> items)
{
    if(items.size()==0){
        std::cout << "No items to perform action";
        // throw std::runtime_error{"No items to perform action"};
    }

    auto res = items.at(0);
    for(unsigned long int i = 1; i < items.size(); i++){
        res = add(res, items.at(i));
    }

    return res;

}

BSPNode *subtract(std::vector<BSPNode *> items)
{
    if(items.size()==0){
        std::cout << "No items to perform action";
        // throw std::runtime_error{"No items to perform action"};
    }

    auto res = items.at(0);
    for(unsigned long int i = 1; i < items.size(); i++){
        res = subtract(res, items.at(i));
    }
    return res;
}
