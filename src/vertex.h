#ifndef VERTEX_H
#define VERTEX_H

#include <ostream>

class Vector2;
class Vector3;

class Vertex
{
    friend std::ostream & operator << (std::ostream& os, Vertex* const v);
    friend std::ostream & operator << (std::ostream& os, Vertex const & v);
public:
    Vertex(float x, float y, float z, Vector3* normal = nullptr, Vector2* uv = nullptr);
    Vertex(Vertex* v);
    /**
     * @brief clone
     * @return Vertex object clone
     */
    Vertex* clone();

    /**
     * @brief add other Vertex to this object
     * @param other Vertex
     * @return this object (after addition)
     */
    Vertex* add(Vertex* other);

    /**
     * @brief subtract other Vertex to this object
     * @param other Vertex
     * @return this object (after subtraction)
     */
    Vertex* subtract(Vertex* other);

private:
  float x, y, z;
  Vector3* normal;
  Vector2* uv;
};

std::ostream & operator << (std::ostream& os, Vertex* const v);
std::ostream & operator << (std::ostream& os, Vertex const & v);

#endif //VERTEX_H
