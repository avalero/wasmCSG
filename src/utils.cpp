#include "utils.h"
#include "constants.h"
#include "triangle.h"

bool isConvexSet(const std::vector<Triangle *> triangles)
{
    for(unsigned long int i = 0; i < triangles.size(); i++){
        for(unsigned long int j = i +1; j < triangles.size(); j++){
            SIDE_CLASSIFICATION side = triangles.at(i)->classifySide(triangles.at(j));
            if(side & CLASSIFY_FRONT) return false;
        }
    }

    return true;
}
