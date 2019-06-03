#include <emscripten/bind.h>
#include <iostream>

#include "polygon.h"
#include "vertex.h"

// using namespace std;
using namespace emscripten;

const double EPSILON = 1e-5;

const int COPLANAR = 0;
const int FRONT = 1;
const int BACK = 2;
const int SPANNING = 3;

using namespace emscripten;

int main()
{
  std::cout << "main" << std::endl;
  Polygon p{4};
  Vertex v{2,1,0};
  std::cout << v << std::endl;
  Vertex u = v.clone();
  v.add(&u);
  std::cout << v << std::endl;
  std::cout << &u << std::endl;
  return 0;
}
