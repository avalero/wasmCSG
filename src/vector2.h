#ifndef VECTOR2_H
#define VECTOR2_H


class Vector2
{
public:
    Vector2();
    Vector2* clone();
    Vector2* add(Vector2* other);
    Vector2* sub(Vector2* other);
    Vector2* multiplyScalar(float t);
};

#endif // VECTOR2_H
