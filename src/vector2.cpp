#include "vector2.h"

Vector2::Vector2(double x, double y):
    x{x},
    y{y}
{

}

Vector2 *Vector2::clone() const
{
    return new Vector2(x,y);
}

Vector2 *Vector2::add(const Vector2 *other)
{
    x += other->x;
    y += other->y;
    return this;

}

Vector2 *Vector2::sub(const Vector2 *other)
{
    x -= other->x;
    y -= other->y;
    return this;

}

Vector2 *Vector2::multiplyScalar(double t)
{
    x *= t;
    y *= t;
    return this;
}
