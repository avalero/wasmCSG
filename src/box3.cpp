#include "box3.h"

#include "vector3.h"
#include <limits>

Box3::Box3(Vector3 *min, Vector3 *max):
    min{min->clone()},
    max{max->clone()}
{}

Box3::Box3(){
    min = new Vector3{
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max()};
    max = new Vector3{
            std::numeric_limits<float>::lowest(),
            std::numeric_limits<float>::lowest(),
            std::numeric_limits<float>::lowest()};
}


Box3::~Box3()
{
    delete min; min = nullptr;
    delete max; max = nullptr;
}

bool Box3::intersectsBox(const Box3 *box) const
{
    // using 6 splitting planes to rule out intersections.
    return !(box->max->x < min->x || box->min->x > max->x ||
            box->max->y < min->y || box->min->y > max->y ||
            box->max->z < min->z || box->min->z > max->z);
}

std::ostream &operator <<(std::ostream &os, const Box3 &box)
{
    os << "min: " << *box.min << std::endl;
    os << "max: " << *box.max << std::endl;
    return os;
}
