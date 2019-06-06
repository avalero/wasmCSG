#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
    friend class ThreeBSP;
public:
    Vector2(double x=0, double y=0);
    Vector2 *clone() const;
    Vector2 *add(const Vector2 *other);
    Vector2 *sub(const Vector2 *other);
    Vector2 *multiplyScalar(double t);

protected:
    double x;
    double y;
};
#endif // VECTOR2_H
