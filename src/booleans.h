#ifndef BOOLEANS_H
#define BOOLEANS_H

#include <vector>

class BSPNode;

BSPNode* intersect(const BSPNode* a, const BSPNode* b);
BSPNode* add(const BSPNode* a, const BSPNode* b);
BSPNode* subtract(const BSPNode* a, const BSPNode* b);

BSPNode* intersect(std::vector<BSPNode*> items);
BSPNode* add(std::vector<BSPNode*> items);
BSPNode* subtract(std::vector<BSPNode*> items);

#endif // BOOLEANS_H
