#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    Vector2(double x=0, double y=0);
    Vector2 *clone();
    Vector2 *add(Vector2 *other);
    Vector2 *sub(Vector2 *other);
    Vector2 *multiplyScalar(double t);

private:
    double x;
    double y;
};
#endif // VECTOR2_H
