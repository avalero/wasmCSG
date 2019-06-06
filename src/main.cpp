#include <emscripten/bind.h>
#include <iostream>

#include "polygon.h"
#include "vertex.h"
#include "node.h"
#include "threebsp.h"

// using namespace std;
using namespace emscripten;

int main()
{
  std::cout << "main" << std::endl;

  Vertex v{2,1,0};
  std::cout << v << std::endl;
  Vertex u = v.clone();
  v.add(&u);
  std::cout <<"v: " << v << std::endl;
  std::cout << "u: " << u << std::endl;

  v.normalize();

  std::cout << "v.normalize: " << v << std::endl;


  v.cross(&u);

  std::cout << "v.cross(u): " << v << std::endl;

  return 0;
}
