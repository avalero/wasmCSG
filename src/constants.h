#ifndef CONSTANTS_H
#define CONSTANTS_H

const float EPSILON = 1e-5f;
const float MINIMUM_RELATION = 0.8f; // 0 -> 1
const float MINIMUM_RELATION_SCALE = 10.f; // should always be >2

enum SIDE_CLASSIFICATION {
    CLASSIFY_COPLANAR = 0,
    CLASSIFY_FRONT = 1,
    CLASSIFY_BACK = 2,
    CLASSIFY_SPANNING = 3
};

#endif // CONSTANTS_H
