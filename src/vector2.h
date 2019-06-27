#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
    friend class ThreeBSP;
public:
    Vector2(float x=0, float y=0);
    Vector2 *clone() const;
    Vector2 *add(const Vector2 *other);
    Vector2 *sub(const Vector2 *other);
    Vector2 *multiplyScalar(float t);

protected:
    float x;
    float y;
};
#endif // VECTOR2_H
