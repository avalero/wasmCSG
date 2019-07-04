#ifndef BOX3_H
#define BOX3_H

class Vector3;

class Box3
{
public:
    Box3(Vector3* min, Vector3* max);
    Box3();
    ~Box3();


    bool intersectsBox(const Box3* box) const;
    Vector3* min;
    Vector3* max;
};

#endif // BOX3_H
